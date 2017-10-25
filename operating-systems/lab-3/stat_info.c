#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>

#define BUFSIZE 50
#define KILO 1024.0
#define DZIEN 86400
#define itob(X) X == 0 ? "yes" : "no"
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb);
static void print_ino(const struct stat *sb);
static void print_perms(const struct stat *sb);
static void print_perms2(const char *file_path);
static void print_linkc(const struct stat *sb);
static void print_owner(const struct stat *sb);
static void print_size(const struct stat *sb);
static void print_laststch(const struct stat *sb);
static void print_lastacc(const struct stat *sb);
static void print_lastmod(const struct stat *sb);
static void print_name(const struct stat *sb, char *name);
/* -------------------------------------------------------------------------------- */

int  main(int argc, char *argv[])
{
  struct stat sb;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if (lstat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
  
  print_type(&sb);
  print_name(&sb, argv[1]);
  print_ino(&sb);
  print_perms(&sb);
  print_perms2(argv[1]);
  print_linkc(&sb);
  print_owner(&sb);
  print_size(&sb);
  print_laststch(&sb);
  print_lastacc(&sb);
  print_lastmod(&sb);
  exit(EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb){
  printf("File type:                ");
  switch (sb->st_mode & S_IFMT) {
  case S_IFBLK:  printf("block device\n");            break;
  case S_IFIFO:  printf("named pipe\n");     		  break;
  case S_IFDIR:  printf("directory\n");      		  break;
  case S_IFREG:  printf("regular file\n");		      break;
  case S_IFLNK:  printf("symbolic link\n");	 	      break;
  case S_IFCHR:  printf("character device\n");        break;
  default:       printf("unknown?\n");                break;
  }
}
/* -------------------------------------------------------------------------------- */

static void print_ino(const struct stat *sb){
  printf("I-node number:            %ld\n", (long) sb->st_ino);
}
/* -------------------------------------------------------------------------------- */

static void print_perms(const struct stat *sb){
  printf("Mode:                     %lo (octal)\n", ((unsigned long) sb->st_mode) & 0777);
}
/* -------------------------------------------------------------------------------- */

static void print_perms2(const char *file_path)
{
	/* Sprawdza rzeczywiste ID uzytkownika */
	printf("Your permissions:         read: %s, write: %s, exec: %s\n", 
			itob(access(file_path, R_OK)), itob(access(file_path, W_OK)), itob(access(file_path, X_OK)));
}

/* -------------------------------------------------------------------------------- */
static void print_linkc(const struct stat *sb){
  printf("Link count:               %ld\n", (long) sb->st_nlink);
}
/* -------------------------------------------------------------------------------- */

static void print_owner(const struct stat *sb){
  struct passwd *pwd;
  struct group * gr;

  if ((pwd = getpwuid(sb->st_uid)) == NULL)
  {
	  perror("getpwuid");
	  exit(EXIT_FAILURE);
  }

  if ((gr = getgrgid(sb->st_gid)) == NULL)
  {
	  perror("getgrgid");
	  exit(EXIT_FAILURE);
  }

  printf("Ownership:                %s(%ld)   %s(%ld)\n", pwd->pw_name, (long) sb->st_uid, gr->gr_name, (long) sb->st_gid);
}
/* -------------------------------------------------------------------------------- */

static void print_size(const struct stat *sb){
  printf("Preferred I/O block size: %ld bytes\n", (long) sb->st_blksize);
  printf("File size:                %.2f kbytes\n",((long long) sb->st_size) / KILO);
  printf("Blocks allocated:         %lld\n",(long long) sb->st_blocks);
}
/* -------------------------------------------------------------------------------- */

static void print_laststch(const struct stat *sb){
  int timediff = (int)difftime(time(NULL), sb->st_ctime);
  printf("Last status change:       %d day(s) ago\n", timediff / DZIEN);
}
/* -------------------------------------------------------------------------------- */

static void print_lastacc(const struct stat *sb){
  int timediff = (int)difftime(time(NULL), sb->st_atime);
  printf("Last status change:       %d day(s) ago\n", timediff / DZIEN);
}
/* -------------------------------------------------------------------------------- */

static void print_lastmod(const struct stat *sb){
  int timediff = (int)difftime(time(NULL), sb->st_mtime);
  printf("Last status change:       %d day(s) ago\n", timediff / DZIEN);
}
/* -------------------------------------------------------------------------------- */

static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);

  if ((sb->st_mode & S_IFMT) == S_IFLNK)
  {
	  char buf[BUFSIZE];
	  readlink(name, buf, BUFSIZE);
	  printf("Link:                     %s -> %s\n", bname, buf);
  }
  else
  {
	   printf("Name of the file:         %s\n", bname);
  }
}
