# ext-data-recovery
When complete, this project will attempt to recover deleted files from ext3 and ext4 filesystems.

Its method is to scan the filesystem journal to look for deleted files' metadata.
Of course, this method only works sometimes, but it is a useful tool to have.

