#include <avr/pgmspace.h>

const char board14[2][693] PROGMEM = {
{3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,53,54,55,56,57,58,59,60,3,4,8,9,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,53,54,55,56,57,58,59,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,37,38,53,54,60,3,4,8,9,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,53,54,55,56,57,58,59,60,3,4,8,9,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,53,54,55,56,57,58,59,60,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,3,4,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,3,4,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,3,4,5,4,5,6,5,6,7,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60},
{181,181,181,181,182,182,182,182,183,183,183,183,184,184,184,184,185,185,185,185,186,186,186,186,187,187,187,187,188,188,188,188,189,189,189,189,190,190,190,190,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,191,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,193,193,193,193,193,193,193,193,193,193,193,194,194,194,194,194,194,194,194,194,194,194,195,195,195,195,195,195,195,195,195,195,195,196,196,196,196,196,196,196,196,196,196,196,197,197,197,197,197,197,197,197,197,197,197,198,198,198,198,198,198,198,198,198,198,198,199,199,199,199,199,199,199,199,199,199,199,200,200,200,200,200,200,200,200,200,200,200,201,201,201,201,201,201,201,201,201,201,201,202,202,202,202,202,202,202,202,202,202,202,203,203,203,203,203,203,203,203,203,203,203,204,204,204,204,204,204,204,204,204,204,204,205,205,205,205,205,205,205,205,205,205,205,206,206,206,206,206,206,206,206,206,206,206,207,207,207,207,207,207,207,207,207,207,207,208,208,208,208,208,208,208,208,208,208,208,209,209,209,209,209,209,209,209,209,209,209,210,210,210,210,210,210,210,210,210,210,210,211,211,211,211,211,211,211,211,211,211,211,212,212,212,212,212,212,212,212,212,212,212,213,213,213,213,213,213,213,213,213,213,213,214,214,214,214,214,214,214,214,214,214,214,215,215,215,215,215,215,215,215,215,215,215,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,216,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,218,218,218,218,219,219,219,219,220,220,220,220,221,221,221,221,222,222,222,222,223,223,223,223,224,224,224,224,225,225,225,225,226,226,226,226,227,227,227,227,228,228,228,228,229,229,229,229,230,230,230,230,231,231,231,231,232,232,232,232,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,233,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,234,235,235,235,236,236,236,237,237,237,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239}
};
