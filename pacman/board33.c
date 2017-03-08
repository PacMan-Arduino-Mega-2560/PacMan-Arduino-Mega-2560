#include <avr/pgmspace.h>

const char board33[2][590] PROGMEM = {
{125,126,128,129,143,144,173,174,125,126,128,129,143,144,173,174,125,126,128,129,143,144,173,174,125,126,128,129,143,144,173,174,125,126,128,129,143,144,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,125,126,128,129,143,144,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,125,126,128,129,143,144,151,152,165,166,167,168,169,170,171,172,173,174,125,126,128,129,143,144,151,152,165,166,167,168,169,170,171,172,173,174,125,126,128,129,143,144,151,152,165,166,173,174,125,126,128,129,143,144,151,152,165,166,173,174,125,126,128,129,143,144,151,152,165,166,173,174,125,126,128,129,143,144,151,152,165,166,173,174,121,122,123,124,125,126,128,129,143,144,151,152,165,166,173,174,128,129,143,144,151,152,165,166,173,174,128,129,143,144,145,146,147,148,149,150,151,152,165,166,173,174,121,122,123,124,125,126,127,128,129,143,144,145,146,147,148,149,150,151,152,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,165,166,173,174,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,165,166,173,174,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,165,166,173,174,121,151,152,165,166,173,174,121,151,152,165,166,173,174,121,151,152,165,166,173,174,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,165,166,167,168,169,170,171,172,173,174,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,165,166,167,168,169,170,171,172,173,174},
{121,121,121,121,121,121,121,121,122,122,122,122,122,122,122,122,123,123,123,123,123,123,123,123,124,124,124,124,124,124,124,124,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,128,128,128,128,128,128,128,128,129,129,129,129,129,129,129,129,130,130,130,130,130,130,130,130,131,131,131,131,131,131,131,131,132,132,132,132,132,132,132,132,133,133,133,133,133,133,133,133,134,134,134,134,134,134,134,134,135,135,135,135,135,135,135,135,136,136,136,136,136,136,136,136,137,137,137,137,137,137,137,137,138,138,138,138,138,138,138,138,139,139,139,139,139,139,139,139,140,140,140,140,140,140,140,140,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,141,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,142,143,143,143,143,143,143,143,143,143,143,143,143,144,144,144,144,144,144,144,144,144,144,144,144,145,145,145,145,145,145,145,145,145,145,145,145,146,146,146,146,146,146,146,146,146,146,146,146,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,147,148,148,148,148,148,148,148,148,148,148,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,151,151,151,151,152,152,152,152,153,153,153,153,154,154,154,154,155,155,155,155,156,156,156,156,157,157,157,157,158,158,158,158,159,159,159,159,160,160,160,160,161,161,161,161,162,162,162,162,163,163,163,163,164,164,164,164,165,165,165,165,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,167,168,168,168,168,168,168,168,169,169,169,169,169,169,169,170,170,170,170,170,170,170,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,171,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172,172}
};