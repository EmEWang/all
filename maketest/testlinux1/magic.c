
// https://segmentfault.com/a/1190000041813940  判断文件为文本文件还是二进制文件（C语言实现）


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int boolean;
#define FALSE 0
#define TRUE  1

/*列举一些常见的文件头，可以自行扩展，比如放到某个配置文件中*/
static const char *with_suffix[] = {".gz", ".rar", ".exe", ".bz2",
                                ".tar", ".xz", ".Z", ".rpm", ".zip",
                                ".a",   ".so", ".o", ".jar", ".dll",
                                ".lib", ".deb", ".I", ".png",".jpg",
                                ".mp3", ".mp4", ".m4a", ".flv", ".mkv",
                                ".rmvb", ".avi",  ".pcap", ".pdf", ".docx",
                                ".xlsx", ".pptx", ".ram", ".mid", ".dwg",
                                NULL};

/*判断某个字符串是否拥有指定后缀*/
static boolean string_has_suffix(const char *str, const char *suffix) {
    int n, m, i = 0;
    char ch = '\0';
    if (str == NULL || suffix == NULL)
    {
        return FALSE;
    }
    n = strlen(str);
    m = strlen(suffix);
    if (n < m) {
        return FALSE;
    }
    for (i = m-1; i >= 0;  i--) {
        if (suffix[i] != str[n - m + i]) {
            return FALSE;
        }
    }
    return TRUE;
}

/*判断文件是否具有特殊后缀*/
static boolean file_has_spec_suffix(const char *fname) {
   const char **suffix = NULL;
   suffix = with_suffix;
   while (*suffix)
   {
      if (string_has_suffix(fname, *suffix))
      {
         return TRUE;
      }
      suffix++;
   }
   return FALSE;
}

/*判断文件是否具有特殊文件头*/
static boolean file_has_spec_header(const char *fname) {
    FILE *fp = NULL;
    size_t len = 0;
    char buf[16] = {0};
    int i = 0;
    boolean retval = FALSE;
    if ((fp = fopen(fname, "r")) == NULL ){
       return FALSE;
    }

    len = sizeof(buf) - 1;
    if (fgets(buf, len, fp) == NULL )  {
       return FALSE;
    }
    if (len < 4)
    {
       return FALSE;
    }
#if defined(__linux__)
    //ELF header
    if (memcmp(buf, "\x7F\x45\x4C\x46", 4) == 0) {
        return TRUE;
    }
#elif defined(_AIX)
    //executable binary
    if (memcmp(buf, "\x01\xDF\x00", 3) == 0) {
        return TRUE;
    }
#elif defined(WIN32)
    // standard exe file, actually, won't go into this case
    if (memcmp(buf, "\x4D\x5A\x90\x00", 4) == 0)
    {
        return TRUE;
    }
#endif
    if (memcmp(buf, "\x50\x4B\x03\x04", 4) == 0) {
        //maybe archive file, eg: jar zip rar sec.
        return TRUE;
    }

    return FALSE;
}


/*测试程序
* 从命令行输入一个文件，返回该文件的类型
*/
int main(int argc, const char **argv) {
   if (argc < 2) {
      printf("usgae: need target file\n");
      exit(-1);
   }
   const char *fname = argv[1];

   if (file_has_spec_suffix(fname)) {
      printf("file %s have special suffix, maybe it's a binary or archive file\n", fname);
   } else if (file_has_spec_header(fname)) {
      printf("file %s have special header, maybe it's a binary or archive file\n", fname);
   } else {
      printf("file %s should be a text file\n", fname);
   }
   return 0;
}
