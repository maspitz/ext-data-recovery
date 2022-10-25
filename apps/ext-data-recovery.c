#include <stdio.h>

#include <com_err.h>
#include <ext2fs/ext2_err.h>

#include <ext2fs/ext2fs.h>

const char *program_name = "ext-data-recovery";


ext2_filsys open_filesystem(const char *device) {
  ext2_filsys current_fs = NULL;
  blk64_t superblock = 0;
  blk64_t blocksize = 0;
  int open_flags = 0;
  int retval;
  io_channel data_io = 0;
  io_manager io_ptr = unix_io_manager;
  retval = ext2fs_open(device, open_flags, superblock, blocksize,
                       io_ptr, &current_fs);
  if (retval == EXT2_ET_SB_CSUM_INVALID) {
    fprintf(stderr, "Warning: checksum error in superblock.\n");
    retval = ext2fs_open(device,
                         open_flags | EXT2_FLAG_IGNORE_CSUM_ERRORS,
                         superblock, blocksize,
                         io_ptr, &current_fs);
  }
  if (retval) {
    com_err(program_name, retval,
            "while trying to open %s", device);
    return current_fs;
  }
  current_fs->default_bitmap_type = EXT2FS_BMAP64_RBTREE;
  retval = ext2fs_read_bitmaps(current_fs);
  if (retval) {
    com_err(device, retval, "while reading filesystem bitmaps");
    retval = ext2fs_close_free(&current_fs);
    if (retval) {
      com_err(program_name, retval, "while closing %s", device);
    }
    return current_fs;
  }

	return current_fs;
}

void close_filesystem(ext2_filsys current_fs) {
  if (current_fs != NULL) {
    ext2fs_close(current_fs);
  }
}



int main(int argc, const char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s filename\n", program_name);
    return 1;
  }

  add_error_table(&et_ext2_error_table);

  const char* fs_filename = argv[1];

  ext2_filsys current_fs = NULL;

  current_fs = open_filesystem(fs_filename);
  if (current_fs == NULL) {
    fprintf(stderr, "%s: Couldn't open filesystem.\n", program_name);
    return 0;
  }

  close_filesystem(current_fs);

/*  journal_t *journal; */


  remove_error_table(&et_ext2_error_table);

  return 0;
}
