#include "../inc/uls.h"

char *file_perm(char *file) {
    char *perm = mx_strnew(11);
    for (int i = 0; i < 10; i++) {
        perm[i] = '-';
    }
    perm[10] = ' ';
    struct stat buf;
    stat(file, &buf);
    if (S_ISDIR(buf.st_mode)) {
        perm[0] = 'd';
    }
    if (buf.st_mode & S_IRUSR) {
        perm[1] = 'r';
    }
    if (buf.st_mode & S_IWUSR) {
        perm[2] = 'w';
    }
    if (buf.st_mode & S_IXUSR) {
        perm[3] = 'x';
    }
    if (buf.st_mode & S_IRGRP) {
        perm[4] = 'r';
    }
    if (buf.st_mode & S_IWGRP) {
        perm[5] = 'w';
    }
    if (buf.st_mode & S_IXGRP) {
        perm[6] = 'x';
    }
    if (buf.st_mode & S_IROTH) {
        perm[7] = 'r';
    }
    if (buf.st_mode & S_IWOTH) {
        perm[8] = 'w';
    }
    if (buf.st_mode & S_IXOTH) {
        perm[9] = 'x';
    }

    if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0)
        perm[10] = '@';
    
    acl_t acl;
    if ((acl = acl_get_file(file, ACL_TYPE_EXTENDED))) {
        acl_free(acl);
        perm[10] ='+';
    }
    return perm;
}
