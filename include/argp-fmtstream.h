#include_next <../argp/argp-fmtstream.h>

#define _IO_fwide_maybe_incompatible (0)

/* A special optimized version of the function above.  It optimizes the
   case of initializing an unoriented byte stream.  */
#define _IO_fwide(__fp, __mode) \
  ({ int __result = (__mode);                                                 \
     if (__result < 0 && ! _IO_fwide_maybe_incompatible)                      \
       {                                                                      \
         if ((__fp)->_mode == 0)                                              \
           /* We know that all we have to do is to set the flag.  */          \
           (__fp)->_mode = -1;                                                \
         __result = (__fp)->_mode;                                            \
       }                                                                      \
     else if (__builtin_constant_p (__mode) && (__mode) == 0)                 \
       __result = _IO_fwide_maybe_incompatible ? -1 : (__fp)->_mode;          \
     else                                                                     \
       __result = _IO_fwide (__fp, __result);                                 \
     __result; })

#define _IO_getc_unlocked(_fp) __getc_unlocked_body (_fp)
#define _IO_peekc_unlocked(_fp)                                         \
  (__glibc_unlikely ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end)        \
   && __underflow (_fp) == EOF                                          \
   ? EOF                                                                \
   : *(unsigned char *) (_fp)->_IO_read_ptr)
#define _IO_putc_unlocked(_ch, _fp) __putc_unlocked_body (_ch, _fp)

# define _IO_getwc_unlocked(_fp)                                        \
  (__glibc_unlikely ((_fp)->_wide_data == NULL                          \
                     || ((_fp)->_wide_data->_IO_read_ptr                \
                         >= (_fp)->_wide_data->_IO_read_end))           \
   ? __wuflow (_fp) : (wint_t) *(_fp)->_wide_data->_IO_read_ptr++)
# define _IO_putwc_unlocked(_wch, _fp)                                  \
  (__glibc_unlikely ((_fp)->_wide_data == NULL                          \
                     || ((_fp)->_wide_data->_IO_write_ptr               \
                         >= (_fp)->_wide_data->_IO_write_end))          \
   ? __woverflow (_fp, _wch)                                            \
   : (wint_t) (*(_fp)->_wide_data->_IO_write_ptr++ = (_wch)))

#define _IO_feof_unlocked(_fp) __feof_unlocked_body (_fp)
#define _IO_ferror_unlocked(_fp) __ferror_unlocked_body (_fp)

