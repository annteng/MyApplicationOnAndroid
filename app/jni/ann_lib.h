#ifndef _ANN_LIB_H_
#define _ANN_LIB_H_
#if 1
class AnnTestClass
{
public:
    AnnTestClass(char p_inChar[80]);
    ~AnnTestClass();
    void DecodeVideo(const char *outfilename, const char *filename);
};
#endif

void DecodeVideo2(const char *outfilename, const char *filename);
#endif
