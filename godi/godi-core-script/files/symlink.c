#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void *
xmalloc(size_t size)
{
  void * ret = malloc(size);
  if ( ret == NULL ){
    fputs("No memory\n",stderr);
    exit(1);
  }
  return ret;
}


/* Prepares an argument vector before calling spawn().
   Note that spawn() does not by itself call the command interpreter
   (getenv ("COMSPEC") != NULL ? getenv ("COMSPEC") :
   ({ OSVERSIONINFO v; v.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
   GetVersionEx(&v);
   v.dwPlatformId == VER_PLATFORM_WIN32_NT;
   }) ? "cmd.exe" : "command.com").
   Instead it simply concatenates the arguments, separated by ' ', and calls
   CreateProcess().  We must quote the arguments since Win32 CreateProcess()
   interprets characters like ' ', '\t', '\\', '"' (but not '<' and '>') in a
   special way:
   - Space and tab are interpreted as delimiters. They are not treated as
   delimiters if they are surrounded by double quotes: "...".
   - Unescaped double quotes are removed from the input. Their only effect is
   that within double quotes, space and tab are treated like normal
   characters.
   - Backslashes not followed by double quotes are not special.
   - But 2*n+1 backslashes followed by a double quote become
   n backslashes followed by a double quote (n >= 0):
   \" -> "
   \\\" -> \"
   \\\\\" -> \\"
*/
#define SHELL_SPECIAL_CHARS "\"\\ \001\002\003\004\005\006\007\010\011\012\013\014\015\016\017\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037"
#define SHELL_SPACE_CHARS " \001\002\003\004\005\006\007\010\011\012\013\014\015\016\017\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037"

static char **
prepare_spawn (char **argv)
{
  size_t argc;
  char **new_argv;
  size_t i;

  /* Count number of arguments.  */
  for (argc = 0; argv[argc] != NULL; argc++)
    ;

  /* Allocate new argument vector.  */
  new_argv = xmalloc((argc + 1) * sizeof *new_argv );

  /* Put quoted arguments into the new argument vector.  */
  for (i = 0; i < argc; i++)
    {
      const char *string = argv[i];

      if (string[0] == '\0')
	new_argv[i] = strdup ("\"\"");
      else if (strpbrk (string, SHELL_SPECIAL_CHARS) != NULL)
	{
	  int quote_around = (strpbrk (string, SHELL_SPACE_CHARS) != NULL);
	  size_t length;
	  unsigned int backslashes;
	  const char *s;
	  char *quoted_string;
	  char *p;

	  length = 0;
	  backslashes = 0;
	  if (quote_around)
	    length++;
	  for (s = string; *s != '\0'; s++)
	    {
	      char c = *s;
	      if (c == '"')
		length += backslashes + 1;
	      length++;
	      if (c == '\\')
		backslashes++;
	      else
		backslashes = 0;
	    }
	  if (quote_around)
	    length += backslashes + 1;
  
	  quoted_string = xmalloc (length + 1);

	  p = quoted_string;
	  backslashes = 0;
	  if (quote_around)
	    *p++ = '"';
	  for (s = string; *s != '\0'; s++)
	    {
	      char c = *s;
	      if (c == '"')
		{
		  unsigned int j;
		  for (j = backslashes + 1; j > 0; j--)
		    *p++ = '\\';
		}
	      *p++ = c;
	      if (c == '\\')
		backslashes++;
	      else
		backslashes = 0;
	    }
	  if (quote_around)
	    {
	      unsigned int j;
	      for (j = backslashes; j > 0; j--)
		*p++ = '\\';
	      *p++ = '"';
	    }
	  *p = '\0';

	  new_argv[i] = quoted_string;
	}
      else
	new_argv[i] = (char *) string;
    }
  new_argv[argc] = NULL;

  return new_argv;
}



static char * 
add_to_file_dir(const char * prefix, const char * suffix)
{
  static char cur_path[MAX_PATH];
  char * last;
  char * ret;
  size_t output_len;
  if ( GetModuleFileName(NULL, cur_path, MAX_PATH)  == 0 ){
    fputs("GetModuleFileName failed\n",stderr);
    exit(2);
  }
  last = strrchr(cur_path, '\\') ;
  if ( last == NULL ){
    fputs("Output of GetModuleFileName contains garbage\n",stderr);
    exit(2);
  }
  *last = '\0';

  output_len = strlen(prefix) + strlen(suffix) + strlen(cur_path) + 1 ;

  ret=xmalloc(output_len);
  snprintf(ret,output_len,"%s%s%s",prefix,cur_path,suffix);

  return ret;
}


int 
main(int argc, char **argv) {
    char **new_argv;
    int k, code;
    new_argv = xmalloc( (argc+2) * sizeof (char *) );
    new_argv[0] = add_to_file_dir("","\\@PROG@");
    new_argv[1] = "@ARGV1@";
    for (k=1; k < argc; k++) new_argv[k+1] = argv[k];
    new_argv[argc+1] = NULL;
    new_argv = prepare_spawn (new_argv);
    code = _spawnv(_P_WAIT, new_argv[0] , (const char **) new_argv );
    if (code == -1) {
        perror("@ARGV1@: Cannot exec @PROG@");
        exit(127);
    }
    else exit(code);
}
