////////////////////////////////////////////////////////////////////////
// COMP1521 23T2 --- Assignment 2: `basin', a simple file synchroniser
// <https://cgi.cse.unsw.edu.au/~cs1521/23T2/assignments/ass2/index.html>
//
// Written by Kevin Le (z5418482) on 24/07/2023.
// A simplified version of rsync where file transfers will send chunks of the file 
// that is different between the sender and reciever
//
// 2023-07-16   v1.1    Team COMP1521 <cs1521 at cse.unsw.edu.au>


#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "basin.h"

// Constants
#define SHIFT_BY_BYTE 8
#define NUM_UPDATES_SIZE 3
#define MAX_L_ENDIAN_SIZE 8
#define SINGLE_BYTE 1

// Function Prototypes
void check_magic(FILE *file, char *magic);
uint64_t read_block_and_get_hash(FILE *file, char *filename);
void go_to_updated_block(int current_block_index, int updated_block_index, FILE *file);
uint64_t convert_little_endian(uint8_t *byte_array, int byte_size);
uint64_t retrieve_little_endian(FILE *file, int byte_size);
void write_as_little_endian(size_t value, int byte_size, FILE *file);
void check_valid_file(FILE *file, char *pathname);
size_t copy_pathname_length(FILE *copy_from, FILE *copy_to);
void copy_pathname(FILE *copy_from, FILE *copy_to, size_t pathname_length, char *pathname);
void get_file_perms(mode_t mode, char *permission);
void get_file_stats(struct stat *file_stat, char *pathname);
void check_leftover_data(FILE *file);
void check_record_size(int bytes_read, int supposed_read_size);
int get_num_records(FILE *file);
void wrapper_fwrite(char *pointer, size_t n_members, FILE *stream);
int copy_num_records(FILE *copy_from, FILE *copy_to);
void wrapper_fputc(size_t value, FILE *file);
uint8_t update_match(int nth_block, uint64_t hash1, uint64_t hash2, uint8_t match_byte);
mode_t udpate_receiver_perms(char *sender_permission, mode_t receiver_mode);

/// @brief Create a TABI file from an array of filenames.
/// @param out_filename A path to where the new TABI file should be created.
/// @param in_filenames An array of strings containing, in order, the files
//                      that should be placed in the new TABI file.
/// @param num_in_filenames The length of the `in_filenames` array. In
///                         subset 5, when this is zero, you should include
///                         everything in the current directory.
void stage_1(char *out_filename, char *in_filenames[], size_t num_in_filenames) {
    FILE *tabi_file = fopen(out_filename, "w");
    check_valid_file(tabi_file, out_filename);

    // write TABI file header
    wrapper_fwrite(TYPE_A_MAGIC, MAGIC_SIZE, tabi_file);
    wrapper_fputc(num_in_filenames, tabi_file);

    for (int record = 0; record < num_in_filenames; record++) {
        // writes length of pathname in reverse order (little-endian) to TABI file
        int pathname_length = strlen(in_filenames[record]); 
        write_as_little_endian(pathname_length, PATHNAME_LEN_SIZE, tabi_file);

        // writes pathname into TABI file (excluding null terminator)
        wrapper_fwrite(in_filenames[record], pathname_length, tabi_file);

        // get size of file to determine block size, then store in little-endian format
        struct stat stat_file;
        get_file_stats(&stat_file, in_filenames[record]);
        off_t file_byte_size = stat_file.st_size;

        int num_blocks = number_of_blocks_in_file(file_byte_size);
        write_as_little_endian(num_blocks, NUM_BLOCKS_SIZE, tabi_file);
    
        FILE *given_file = fopen(in_filenames[record], "r");
        check_valid_file(given_file, in_filenames[record]);
       
        // gets hash for each block and write them into TABI file
        for (int i = 0; i < num_blocks; i++) {
            uint64_t hash = read_block_and_get_hash(given_file, in_filenames[record]);
            write_as_little_endian(hash, HASH_SIZE, tabi_file);
        }

        fclose(given_file);
    }
    
    fclose(tabi_file);
}


/// @brief Create a TBBI file from a TABI file.
/// @param out_filename A path to where the new TBBI file should be created.
/// @param in_filename A path to where the existing TABI file is located.
void stage_2(char *out_filename, char *in_filename) {
    FILE *tabi_file = fopen(in_filename, "r");
    check_valid_file(tabi_file, in_filename);
    
    check_magic(tabi_file, TYPE_A_MAGIC);

    // write TBBI header
    FILE *tbbi_file = fopen(out_filename, "w");
    check_valid_file(tbbi_file, out_filename);

    wrapper_fwrite(TYPE_B_MAGIC, MAGIC_SIZE, tbbi_file);    
    
    int num_records = copy_num_records(tabi_file, tbbi_file);
    int record = 0;

    while (record < num_records && !feof(tabi_file)) {
        // write pathname length and pathname from TABI to TBBI
        size_t pathname_length = copy_pathname_length(tabi_file, tbbi_file);

        char pathname[pathname_length + 1];
        copy_pathname(tabi_file, tbbi_file, pathname_length, pathname); 

        // write number of blocks from TABI to TBBI
        size_t num_blocks = retrieve_little_endian(tabi_file, NUM_BLOCKS_SIZE);
        write_as_little_endian(num_blocks, NUM_BLOCKS_SIZE, tbbi_file);

        // open copy of file to compare hashes; if file doesn't exist, add 0x00 as match_byte
        uint8_t match_byte = 0x00;
        FILE *own_matching_file = fopen(pathname, "r");
        
        int nth_block = 0;
        while (nth_block < num_blocks && !feof(tabi_file)) {
            uint64_t tabi_hash = retrieve_little_endian(tabi_file, HASH_SIZE);

            if (own_matching_file != NULL) {       
                uint64_t receiver_hash = read_block_and_get_hash(own_matching_file, pathname);
                match_byte = update_match(nth_block, tabi_hash, receiver_hash, match_byte);
            }

            if ((nth_block + 1) % MATCH_BYTE_BITS == 0) {
                wrapper_fputc(match_byte, tbbi_file);
                match_byte = 0x00;
            } 

            nth_block++;
        }
        
        if (num_blocks > 0) {
            wrapper_fputc(match_byte, tbbi_file);
        }      

        if (own_matching_file != NULL) {
            fclose(own_matching_file);   
        }
        
       record++;
    }

    check_leftover_data(tabi_file);
    fclose(tabi_file);
    fclose(tbbi_file);
}


/// @brief Create a TCBI file from a TBBI file.
/// @param out_filename A path to where the new TCBI file should be created.
/// @param in_filename A path to where the existing TBBI file is located.
void stage_3(char *out_filename, char *in_filename) {
    
    // check and set up header for TBBI and TCBI file respectively
    FILE *tbbi_file = fopen(in_filename, "r");
    check_valid_file(tbbi_file, in_filename);
    
    check_magic(tbbi_file, TYPE_B_MAGIC);

    FILE *tcbi_file = fopen(out_filename, "w");
    check_valid_file(tcbi_file, out_filename);

    wrapper_fwrite(TYPE_C_MAGIC, MAGIC_SIZE, tcbi_file);

    int num_records = copy_num_records(tbbi_file, tcbi_file);
    int record = 0;

    while (record < num_records && !feof(tbbi_file)) {
        // write pathname length and pathname respectively from TBBI to TCBI file
        size_t pathname_length = copy_pathname_length(tbbi_file, tcbi_file);
    
        char pathname[pathname_length + 1];
        copy_pathname(tbbi_file, tcbi_file, pathname_length, pathname);

        // get mode/file size of TBBI file then store them into TCBI
        struct stat file_stat;
        get_file_stats(&file_stat, pathname);

        mode_t mode = file_stat.st_mode;
        off_t file_size = file_stat.st_size;

        char permission[] = "-rwxrwxrwx";
        get_file_perms(mode, permission);

        wrapper_fwrite(permission, MODE_SIZE, tcbi_file);
        write_as_little_endian(file_size, FILE_SIZE_SIZE, tcbi_file);

        // write num updates to tcbi file
        size_t num_blocks = retrieve_little_endian(tbbi_file, NUM_BLOCKS_SIZE);
        size_t num_match_bytes = num_tbbi_match_bytes(num_blocks);
        
        // loop through matches in TBBI and determine which bytes need to be
        // updated by finding (not padded) 0s in match bytes 
        size_t block_index_to_update[num_blocks];
        
        int num_updates = 0;
        int nth_block = 0;
        int nth_match_byte = 0;
        int match_byte;

        while (nth_match_byte < num_match_bytes) {
            match_byte = fgetc(tbbi_file);

            if (match_byte == EOF && nth_match_byte < num_match_bytes) {
                fprintf(stderr, "Invalid TBBI file\n");
                exit(1);
            }
            
            uint8_t bit_mask = 0x80;
            for (int i = 0; i < MATCH_BYTE_BITS; i++) {
                if (((match_byte & bit_mask) == 0) && nth_block < num_blocks) {
                    block_index_to_update[num_updates] = nth_block;
                    num_updates++;
                } else if (((match_byte & bit_mask) != 0) && nth_block >= num_blocks) {
                    fprintf(stderr, "incorrect padding\n");
                    exit(1);
                }

                nth_block++;
                bit_mask >>= 1;
            }

            nth_match_byte++;
        }
        
        // write number of updates to TCBI file
        write_as_little_endian(num_updates, NUM_UPDATES_SIZE, tcbi_file);

        // get block of data from own copy of file that needs to be updated
        // and write to TCBI file
        FILE *file_to_update = fopen(pathname, "r");
        check_valid_file(file_to_update, pathname);
        
        int current_block_index = 0;

        for (int i = 0; i < num_updates; i++) {
            size_t update_block_index = block_index_to_update[i];

            // write index of block being updated into TCBI file
            write_as_little_endian(update_block_index, BLOCK_INDEX_SIZE, tcbi_file);

            go_to_updated_block(current_block_index, update_block_index, file_to_update);
            
            char update_block[BLOCK_SIZE];
            size_t bytes_read = fread(update_block, SINGLE_BYTE, BLOCK_SIZE, file_to_update);
            current_block_index = update_block_index + 1;
            
            if (bytes_read == 0) {
                fprintf(stderr, "not enough blocks in file\n");
                exit(1);
            }
            
            // write udpate length and update data respectively into TCBI file
            write_as_little_endian(bytes_read, UPDATE_LEN_SIZE, tcbi_file);
            wrapper_fwrite(update_block, bytes_read, tcbi_file);
        }

        fclose(file_to_update);
        record++;
    }

    check_leftover_data(tbbi_file);
    fclose(tbbi_file);
    fclose(tcbi_file);

}


/// @brief Apply a TCBI file to the filesystem.
/// @param in_filename A path to where the existing TCBI file is located.
void stage_4(char *in_filename) {
    FILE *tcbi_file = fopen(in_filename, "r");
    check_valid_file(tcbi_file, in_filename);
    
    // check header and get num_records of TCBI file
    check_magic(tcbi_file, TYPE_C_MAGIC);

    int num_records = get_num_records(tcbi_file);
    int record = 0;
    
    while (record < num_records && !feof(tcbi_file)) {
        // get pathname length and pathname from TCBI file to update receiver's version of it
        size_t pathname_length = retrieve_little_endian(tcbi_file, PATHNAME_LEN_SIZE);

        char pathname[pathname_length + 1];
        size_t bytes_read = fread(pathname, SINGLE_BYTE, pathname_length, tcbi_file);
        pathname[pathname_length] = '\0';
        check_record_size(bytes_read, pathname_length);
        
        // get sender's permission of file
        char sender_permission[MODE_SIZE];
        bytes_read = fread(sender_permission, SINGLE_BYTE, MODE_SIZE, tcbi_file);
        check_record_size(bytes_read, MODE_SIZE);
        
        // checks if file exists by checking for its stats
        // if it doesn't exist, create a new file and get its metadata then
        struct stat receiver_file_stat;

        if (stat(pathname, &receiver_file_stat) != 0) {
            FILE *file_to_update = fopen(pathname, "w");
            fclose(file_to_update);
            
            if (stat(pathname, &receiver_file_stat) != 0) {
                fprintf(stderr, "Error reading file metadata\n");
                exit(1);
            }
        }

        // make receiver_mode same as sender permission;
        mode_t receiver_mode = receiver_file_stat.st_mode;
        receiver_mode = udpate_receiver_perms(sender_permission, receiver_mode);

        if (chmod(pathname, receiver_mode) == -1) {
            perror(pathname);
            exit(1);
        }

        // update receiver's files to that of sender's
        FILE *file_to_update = fopen(pathname, "r+");

        size_t sender_file_size = retrieve_little_endian(tcbi_file, FILE_SIZE_SIZE);

        size_t num_updates = retrieve_little_endian(tcbi_file, NUM_UPDATES_SIZE);
        size_t nth_update = 0;
        
        while (nth_update < num_updates && !feof(tcbi_file)) {
            size_t block_index = retrieve_little_endian(tcbi_file, BLOCK_INDEX_SIZE);
            
            // go to indexed block and overwrite with update_data in TCBI file
            if (fseek(file_to_update, BLOCK_SIZE * block_index, SEEK_SET) != 0) {
                perror(pathname);
                exit(1);
            }

            size_t update_length = retrieve_little_endian(tcbi_file, UPDATE_LEN_SIZE);

            char update_data[update_length];
            bytes_read = fread(update_data, SINGLE_BYTE, update_length, tcbi_file);
            check_record_size(bytes_read, update_length);

            wrapper_fwrite(update_data, update_length, file_to_update);
            nth_update++;
        }

        // synchronises file size of receiver to be that of sender's
        if (truncate(pathname, sender_file_size) != 0) {
            perror(pathname);
            exit(1);
        }
        
        fclose(file_to_update);
        record++;
    }

    check_leftover_data(tcbi_file);
    fclose(tcbi_file);
}


/**
 * @brief Checks start of a file for magic number of certain file type and exits 
 *        with 1 the magic numbers do not match with the file type
 */
void check_magic(FILE *file, char *magic) {
    int magic_byte;
    for (int i = 0; i < MAGIC_SIZE; i++) {
        magic_byte = fgetc(file);
        
        if (magic_byte != magic[i] || magic_byte == EOF || ferror(file)) {
            fprintf(stderr, "Invalid magic numbers for file\n");
            exit(1);
        }
    }
}

/**
 * @brief Reads a block of data and produce a hash for it
 * @param file The FILE stream pointer where the block of data is being converted to a hash
 * @param filename A string containing the path to the file which this function is operating on
 * 
 * @return a uint64_t hash variable determined by the hash_block() function 
 */
uint64_t read_block_and_get_hash(FILE *file, char *filename) {
    char blocks[BLOCK_SIZE];
    size_t bytes_read = fread(blocks, SINGLE_BYTE, BLOCK_SIZE, file);

    if (ferror(file)) {
        fprintf(stderr, "Error reading given file: %s\n", filename);
        clearerr(file);
        exit(1);
    }

     return hash_block(blocks, bytes_read);
}

/**
 * @brief Continuously reads in blocks of data until the intended block index is reached.
 *        It will also error-check for block indexes being larger than the file size
 * @param current_block_index The current block index at time of calling this function
 * @param updated_block_index The block index that we want to traverse to
 */
void go_to_updated_block(int current_block_index, int updated_block_index, FILE *file) {
    while (current_block_index < updated_block_index) {
        char block[BLOCK_SIZE];
        int bytes_read = fread(block, SINGLE_BYTE, BLOCK_SIZE, file);

        check_record_size(bytes_read, BLOCK_SIZE);
        
        current_block_index++;
    }
}

/**
 * @brief Converts a little-endian value to its proper value from an array
 * @param array The array containg the bytes of the little-endian value
 * @param byte_size The size of the read-in value in bytes
 * 
 * @return A uint64_t variable containing the intended value of the little-endian value
 */
uint64_t convert_little_endian(uint8_t *byte_array, int byte_size) {
    uint64_t input = 0;

    for (int i = 0; i < byte_size; i++) {
        uint64_t inserted_byte = byte_array[i];
        inserted_byte <<= i * SHIFT_BY_BYTE;
        input |= inserted_byte;
    }

    return input;
} 

/**
 * @brief Will read in bytes of a little-endian value and swap the bytes so they represent 
 *        the value as intended.
 * @param file A FILE pointer of the file where the little-endian value is stored
 * @param byte_size the size in bytes of the little-endian value stored in the file
 * 
 * @return A uint64_t variable called value containing the value of the little-endian data
 */
uint64_t retrieve_little_endian(FILE *file, int byte_size) {
    uint8_t read_input[MAX_L_ENDIAN_SIZE] = {0};
    int bytes_read = fread(read_input, SINGLE_BYTE, byte_size, file);

    check_record_size(bytes_read, byte_size);
    
    uint64_t value = convert_little_endian(read_input, byte_size);

    return value;
}

/**
 * @brief Writes some value of a certain size into a file in little-endian format
 * @param value The data of type size_t which is to be stored in little-endian
 * @param byte_size The size of the value being stored in bytes
 * @param file The FILE pointer of the file where the value will be stored
 */
void write_as_little_endian(size_t value, int byte_size, FILE *file) {
    for (int i = 0; i < byte_size; i++) {
        if (fputc(value, file) == EOF) {
            fprintf(stderr, "Error writing data\n");
            exit(1);
        }

        value >>= SHIFT_BY_BYTE;
    }
}

/**
 * @brief Checks whether the file opened was successful. Exits program with 1 if unsuccessful
 * @param file A FILE pointer of the intended file being opened
 * @param pathname A string of the path to the file being opened
 */
void check_valid_file(FILE *file, char *pathname) {
     if (file == NULL) {
        perror(pathname);
        exit(1);
    }
}

/**
 * @brief Read and return the value for number of records stored in a file
 * @param file A FILE pointer to the file to retrieve this data from
 * 
 * @return An integer num_records 
 */
int get_num_records(FILE *file) {
    int num_records = fgetc(file);

    if (num_records == EOF) {
        fprintf(stderr, "Invalid header\n");
        exit(1);
    }

    return num_records;
}

/**
 * @brief Reads the pathname length from one file and writes it into another file, returning 
 *        that value to the caller after copying
 * @param copy_from A FILE pointer to the file where pathname length will be copied from
 * @param copy_to A FILE pointer to the file where pathname length will be copied to
 * 
 * @return A size_t variable containing the value of the pathname length
 */
size_t copy_pathname_length(FILE *copy_from, FILE *copy_to) {
    size_t pathname_length = retrieve_little_endian(copy_from, PATHNAME_LEN_SIZE);
    write_as_little_endian(pathname_length, PATHNAME_LEN_SIZE, copy_to);

    return pathname_length;
}

/**
 * @brief Reads the pathname from one file and writes it into another, storing it into a string
 *        given by the caller
 * @param copy_from A FILE pointer to the file where the pathname will be copied from
 * @param copy_to A FILE pointer to the file where the pathname will be copied to
 * @param pathname_length The size of the pathname in bytes
 * @param pathname A char array where the pathname read from the file will be stored
 */
void copy_pathname(FILE *copy_from, FILE *copy_to, size_t pathname_length, char *pathname) {
    int bytes_read = fread(pathname, SINGLE_BYTE, pathname_length, copy_from);
    pathname[pathname_length] =  '\0';
    
    check_record_size(bytes_read, pathname_length);

    wrapper_fwrite(pathname, pathname_length, copy_to);
}

/**
 * @brief Deconstructs the mode of the file to represent its permissions in a string format
 * @param mode The mode of the file which contains the file's type and permissions
 * @param permission A char array where the permission of the file will be represented in
 */
void get_file_perms(mode_t mode, char *permission) {
    if (S_ISDIR(mode)) {
        permission[0] = 'd';
    } 

    for (int i = 1; i < MODE_SIZE; i++) {
        if (!(mode & (1 << (i - 1)))) {
            permission[MODE_SIZE - i] = '-';
        }
    }
}

/**
 * @brief Retrieves metadata of a file and stores it into a pointer
 * @param file_stat A pointer to a struct stat variable which will store the metadata of the file
 * @param pathname A char array of the path to the file where the metadata will be retrieved
 */
void get_file_stats(struct stat *file_stat, char *pathname) {
    if (stat(pathname, file_stat) != 0) {
        perror(pathname);
        exit(1);
    }
}

/**
 * @brief Checks whether there is still data left in the file after all intended bytes were read
 *        and exits with 1 if there is leftover data
 * @param file A FILE pointer for the file that was being read
 */
void check_leftover_data(FILE *file) {
    char buffer[1];
    if (fread(buffer, SINGLE_BYTE, SINGLE_BYTE, file) > 0) {
        fprintf(stderr, "num records too small\n");
        exit(1);
    }
}

/**
 * @brief Checks whether the number of bytes read by fread is less than intended and exits
 *        with 1 if it is
 * @param bytes_read The number of bytes that was read by an fread() function
 * @param supposed_read_size The number of bytes expected for the fread() function to read
 */
void check_record_size(int bytes_read, int supposed_read_size) {
    if (bytes_read < supposed_read_size) {
        fprintf(stderr, "record too small\n");
        exit(1);
    }
}

/**
 * @brief A wrapper function for fwrite() which also error checks for errors in writing. Exits
 *        with 1 if error is detected
 * @param array A char array where the function will write the data from
 * @param n_members Number of times fwrite() should write into a file
 * @param stream A FILE pointer of file where data is being written
 */
void wrapper_fwrite(char *array, size_t n_members, FILE *stream) {
    if (fwrite(array, SINGLE_BYTE, n_members, stream) == 0) {
        fprintf(stderr, "Error writing to file\n");
        exit(1);
    }

}

/**
 * @brief Reads number of records in header of one file and writes into another file
 * @param copy_from A FILE pointer of the file where num_records will be read from
 * @param copy_to A FILE pointer of the file where num_records will be written into
 * 
 * @return An integer of num_records which was stored in the file under copy_from 
 */
int copy_num_records(FILE *copy_from, FILE *copy_to) {
    int num_records = get_num_records(copy_from);

    if (fputc(num_records, copy_to) == 0) {
        fprintf(stderr, "Error writing num records\n");
        exit(1);
    }

    return num_records;
}

/**
 * @brief A wrapper function of fputc() which checks for errors when writing the byte into the file
 * @param value A number with data type size_t that will be written into the file
 * @param file A FILE pointer to the file where the value will be written into 
 */
void wrapper_fputc(size_t value, FILE *file) {
    if (fputc(value, file) == 0 && value != 0) {
        fprintf(stderr, "Error writing byte\n");
        exit(1);
    }
}

/**
 * @brief Takes in two hashes and compares them. If they are identical, update the given match byte
 * @param nth_block Integer denoting how many blocks has been read so far. Used to determine
 *                  which bit of the match_byte is going to change if applicable
 * @param hash1 A uint64_t variable containing one hash
 * @param hash2 A uint64_t variable containing another hash
 * @param match_byte The current byte being operated on to represent which blocks of data match
 * 
 * @return A uint8_t variable match_byte which is the same match_byte given by the caller after it
 *         has been updated
 */
uint8_t update_match(int nth_block, uint64_t hash1, uint64_t hash2, uint8_t match_byte) {
    if (hash1 == hash2) {
        uint8_t bit_mask = 1;
        match_byte |= bit_mask << (SHIFT_BY_BYTE - (nth_block % MATCH_BYTE_BITS) - 1);
    }

    return match_byte;
}

/**
 * @brief Receives user mode and sender mode and sets receiver mode to be the same as sender's
 * 
 * @param sender_permission The char array containing the mode of the sender where the permission
 *                          will be set to
 * @param receiver_mode The user's mode of their respective file. This variable will be changed to match
 *                      the sender's permissions
 * @return A mode_t variable 
 */
mode_t udpate_receiver_perms(char *sender_permission, mode_t receiver_mode) {
    int valid_permission = 1;
    int invalid_permission = 0x3FF - valid_permission;
    
    for (int i = 1; i < MODE_SIZE; i++) {
        if (sender_permission[MODE_SIZE - i] == '-') {
            receiver_mode &= invalid_permission;
        } else {
            receiver_mode |= valid_permission;
        }
        valid_permission <<= 1;
        invalid_permission = 0x3FF - valid_permission;
    }

    return receiver_mode;
}