cmake_minimum_required(VERSION 3.20)

project(
  ext-data-recovery
  VERSION 0.1
  DESCRIPTION "Recover deleted inodes and associated data from an ext3 or ext4 file system's journal"
  LANGUAGES C)
find_package(PkgConfig REQUIRED)
pkg_check_modules(COM_ERR REQUIRED com_err)
pkg_check_modules(EXT2FS REQUIRED ext2fs)

#add_subdirectory(src)
add_subdirectory(apps)

