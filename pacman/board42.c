#include <avr/pgmspace.h>

const char board42[2][660] PROGMEM = {
{210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,218,219,233,234,238,239,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,218,219,233,234,238,239,190,191,218,219,233,234,238,239,190,191,218,219,233,234,238,239,190,191,218,219,233,234,238,239,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,218,219,233,234,238,239,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,210,211,218,219,233,234,238,239,190,191,192,193,194,195,196,197,210,211,218,219,233,234,238,239,190,191,192,193,194,195,196,197,210,211,218,219,233,234,238,239,190,191,196,197,210,211,218,219,233,234,238,239,190,191,196,197,210,211,218,219,233,234,238,239,190,191,196,197,210,211,218,219,233,234,238,239,190,191,196,197,210,211,218,219,233,234,238,239,190,191,196,197,210,211,218,219,233,234,238,239,190,191,196,197,210,211,212,213,214,215,216,217,218,219,233,234,238,239,190,191,196,197,210,211,212,213,214,215,216,217,218,219,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,233,234,238,239,190,191,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,233,234,238,239,190,191,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,233,234,238,239,190,191,218,219,233,234,238,239,190,191,218,219,233,234,238,239,190,191,218,219,233,234,238,239},
{61,61,61,61,61,61,61,61,62,62,62,62,62,62,62,62,63,63,63,63,63,63,63,63,64,64,64,64,64,64,64,64,65,65,65,65,65,65,65,65,66,66,66,66,66,66,66,66,67,67,67,67,67,67,67,67,68,68,68,68,68,68,68,68,69,69,69,69,69,69,69,69,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,72,72,72,72,72,72,72,72,73,73,73,73,73,73,73,73,74,74,74,74,74,74,74,74,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,77,77,77,77,77,77,77,77,78,78,78,78,78,78,78,78,79,79,79,79,79,79,79,79,80,80,80,80,80,80,80,80,81,81,81,81,81,81,81,81,82,82,82,82,82,82,82,82,83,83,83,83,83,83,83,83,84,84,84,84,84,84,84,84,85,85,85,85,85,85,85,85,86,86,86,86,86,86,86,86,87,87,87,87,87,87,87,87,88,88,88,88,88,88,88,88,89,89,89,89,89,89,89,89,90,90,90,90,90,90,90,90,91,91,91,91,91,91,91,91,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,94,94,94,94,94,94,94,94,94,94,94,94,95,95,95,95,95,95,95,95,95,95,95,95,96,96,96,96,96,96,96,96,96,96,96,96,97,97,97,97,97,97,97,97,97,97,97,97,98,98,98,98,98,98,98,98,98,98,98,98,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,102,102,102,102,102,102,102,102,103,103,103,103,103,103,103,103,104,104,104,104,104,104,104,104,105,105,105,105,105,105,105,105,106,106,106,106,106,106,106,106,107,107,107,107,107,107,107,107,108,108,108,108,108,108,108,108,109,109,109,109,109,109,109,109,110,110,110,110,110,110,110,110,111,111,111,111,111,111,111,111,112,112,112,112,112,112,112,112,113,113,113,113,113,113,113,113,114,114,114,114,114,114,114,114,115,115,115,115,115,115,115,115,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,118,118,118,118,118,118,118,118,119,119,119,119,119,119,119,119,120,120,120,120,120,120,120,120}
};
