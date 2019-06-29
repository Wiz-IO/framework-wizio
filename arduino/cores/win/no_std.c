
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
