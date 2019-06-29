

#if 0
int isdigit(int c) { return (c >= '0' && c <= '9'); }
int isalpha(int c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }
int isalnum(int c) { return (isalpha(c) || isdigit(c)); }
int iscntrl(int c) { return (c == 127 || (c >= 0 && c <= 31)); }
int islower(int c) { return (c >= 'a' && c <= 'z'); }
int isprint(int c) { return (c >= 0x20 && c <= 0x7E); }
int isgraph(int c) { return (isprint(c) && c != ' '); }
int isspace(int c) { return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'); }
int ispunct(int c) { return (isprint(c) && !isspace(c) && !isalnum(c)); }
int isupper(int c) { return (c >= 'A' && c <= 'Z'); }
int isxdigit(int c) { return (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')); }
int isblank(int c) { return (c == ' ' || c == '\t'); }
int isascii(int c) { return c >= 0 && c < 128; }
int toascii(int c) { return c & 0177; }
#endif 

static const char *str_digits = "0123456789abcdef";

void reverse(char *begin, char *end)
{
    char *is = begin;
    char *ie = end - 1;
    while (is < ie)
    {
        char tmp = *ie;
        *ie = *is;
        *is = tmp;
        ++is;
        --ie;
    }
}

char *utoa(unsigned value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        unsigned quotient = value;
        do
        {
            const unsigned tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        reverse(result, out);
        *out = 0;
    }
    return result;
}

char *ultoa(unsigned long value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        unsigned long quotient = value;
        do
        {
            const unsigned long tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        reverse(result, out);
        *out = 0;
    }
    return result;
}

#include <stdarg.h>
int log_printf(const char *frm, ...)
{
    va_list arg;
    va_start(arg, frm);
    vprintf(frm, arg);
    va_end(arg);
    return 0;
}

void log_buf(const char *text, const unsigned char *buf, unsigned int len)
{
    if (len > 512)
        len = 512;
    char bufferChar[17];
    char bufferDump[512];
    unsigned int i, idx = 0;
    memset(bufferDump, 0, sizeof(bufferDump));
    snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "[DMP] %s (%u bytes)\n", text, len);
    log_printf(bufferDump);
    idx = 0;
    memset(bufferChar, 0, sizeof(bufferChar));
    for (i = 0; i < len; i++)
    {
        if (i >= 4096)
            break;
        if (i % 16 == 0)
        {
            if (i > 0)
            {
                snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "  %s\n", bufferChar);
                log_printf(bufferDump);
                idx = 0;
                memset(bufferChar, 0, sizeof(bufferChar));
            }
            idx += snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "%04X: ", (unsigned int)i);
        }
        idx += snprintf(bufferDump + idx, sizeof(bufferDump) - idx, " %02X", (unsigned int)buf[i]);
        bufferChar[i % 16] = (buf[i] > 31 && buf[i] < 127) ? buf[i] : '.';
    }
    if (len > 0)
    {
        for (/* i = i */; i % 16 != 0; i++)
            idx += snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "   ");
        snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "  %s\n", bufferChar);
        log_printf(bufferDump);
    }
}
