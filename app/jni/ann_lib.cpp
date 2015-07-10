extern "C" {
#include <math.h>
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}
#include <stdio.h>
#include <stdlib.h>
#include "ann_lib.h"
#include <string.h>
#include <android/log.h>
#include <pthread.h>


#define INBUF_SIZE 50000
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096
char msg[80];
#define ANN_DEBUG sprintf(msg, "line : %d", __LINE__); __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);


AnnTestClass::AnnTestClass(/*char p_inChar[80]*/)
{
   /* FILE* pFile = fopen("aaa", "w");
    if (pFile)
    {
        fprintf(pFile, "asd");
        fclose(pFile);
    }

   // hello[80];
    if (p_inChar)
        sprintf(p_inChar,"Hello, hello, 2222olala" );*/


}

AnnTestClass::~AnnTestClass()
{

}

static void pgm_save(unsigned char *buf, int wrap, int xsize, int ysize,
                     char *filename)
{
    FILE *f;
    int i;
    f = fopen(filename,"w");
    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
    for (i = 0; i < ysize; i++)
        fwrite(buf + i * wrap, 1, xsize, f);
    fclose(f);
}

static void outputFrame(unsigned char *buf, int wrap, int xsize, int ysize,
                     const char *filename)
{
    FILE *f;
    int i;
    f = fopen(filename,"ab");
   // fwrite(buf, xsize*ysize*3/2, f);
    //fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
    sprintf(msg, "xsize=%d, ysize=%d, wrap=%d\n", xsize, ysize, wrap);
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
    /*for (i = 0; i < ysize; i++)
        fwrite(buf + i * wrap, 1, xsize, f); */

    fwrite(buf, 1, xsize*ysize*3/2, f);
    fclose(f);
}

static int decode_write_frame(const char *outfilename, AVCodecContext *avctx,
                              AVFrame *frame, int *frame_count, AVPacket *pkt, int last)
{
    int len, got_frame;
    char buf[1024];
    ANN_DEBUG
    len = avcodec_decode_video2(avctx, frame, &got_frame, pkt);

    if (len < 0) {
    //av_err2str(len);
      //  sprintf(msg, "Error decoding video frame (%s)\n", );
         av_make_error_string(msg, 80, len);
         __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
        fprintf(stderr, "Error while decoding frame %d\n", *frame_count);
        return len;
    }
    sprintf(msg, "%d len = %d\n",__LINE__, len);
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);

    if (got_frame) {

        sprintf(msg, "%d Saving %sframe %3d\n", __LINE__, last ? "last " : "", *frame_count);
        __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
        fflush(stdout);
        /* the picture is allocated by the decoder, no need to free it */
        snprintf(buf, sizeof(buf), outfilename, *frame_count);
       // pgm_save(frame->data[0], frame->linesize[0],
       //          avctx->width, avctx->height, buf);
       outputFrame(frame->data[0], frame->linesize[0],
                        avctx->width, avctx->height, outfilename);
        (*frame_count)++;
    }
    if (pkt->data) {
        pkt->size -= len;
        pkt->data += len;
    }

    sprintf(msg, "%d pkt->size = %d\n",__LINE__, pkt->size);
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
    return 0;
}

void DecodeVideo2(const char *outfilename, const char *filename)
{
    /* must be called before using avcodec lib */

    avcodec_register_all();
    FILE* outFile = fopen(outfilename, "wb");
    if (outFile)
    {
        __android_log_write(ANDROID_LOG_DEBUG, "jni_test", "out file exists");
        fclose(outFile);
    }
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", "Decode video file start.....");
    AVCodec *codec;
    AVCodecContext *c= NULL;
    int frame_count;
    FILE *f;
    AVFrame *frame;
    uint8_t inbuf[INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];
    AVPacket avpkt;
    av_init_packet(&avpkt);
    /* set end of buffer to 0 (this ensures that no overreading happens for damaged mpeg streams) */
    memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);
    ANN_DEBUG

    printf("Decode video file %s to %s\n", filename, outfilename);
    sprintf(msg, "Decode video file %s to %s\n", filename, outfilename);
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);

    ANN_DEBUG
    /* find the mpeg1 video decoder */
    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    ANN_DEBUG

    if (!codec) {
        ANN_DEBUG
        sprintf(msg, "Codec not found\n");
        __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }
    ANN_DEBUG
    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }
    ANN_DEBUG
    sprintf(msg, "truncated is removed\n");
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
   /* if(codec->capabilities&CODEC_CAP_TRUNCATED)
        c->flags|= CODEC_FLAG_TRUNCATED; */
        /* we do not send complete frames */
    /* For some codecs, such as msmpeg4 and mpeg4, width and height
       MUST be initialized there because this information is not
       available in the bitstream. */
    /* open it */
    ANN_DEBUG
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }
    ANN_DEBUG
    f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }
    ANN_DEBUG
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }
    ANN_DEBUG

    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);

    for (;;) {
        ANN_DEBUG
        avpkt.size = fread(inbuf, 1, INBUF_SIZE, f);
        sprintf(msg, "avpkt.size = %d, inbuf=0x%x _____ %x\n", avpkt.size, inbuf[0], inbuf[1]);
        if (avpkt.size == 0)
            break;
        __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
        /* NOTE1: some codecs are stream based (mpegvideo, mpegaudio)
           and this is the only method to use them because you cannot
           know the compressed data size before analysing it.
           BUT some other codecs (msmpeg4, mpeg4) are inherently frame
           based, so you must call them with all the data for one
           frame exactly. You must also initialize 'width' and
           'height' before initializing them. */
        /* NOTE2: some codecs allow the raw parameters (frame size,
           sample rate) to be changed at any frame. We handle this, so
           you should also take care of it */
        /* here, we use a stream based decoder (mpeg1video), so we
           feed decoder and see if it could decode a frame */
        avpkt.data = inbuf;
        ANN_DEBUG
        while (avpkt.size > 0)
        {
            if (decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 0) < 0)
            {
                sprintf(msg, "fail to write decode frame\n");
                __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
                exit(1);
            }
            sprintf(msg, "%d avpkt.size = %d, frame_count = %d\n", __LINE__, avpkt.size, frame_count);
            __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);
        }
    }

    /* some codecs, such as MPEG, transmit the I and P frame with a
       latency of one frame. You must do the following to have a
       chance to get the last frame of the video */
    ANN_DEBUG
    avpkt.data = NULL;
    avpkt.size = 0;


    decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 1);
    ANN_DEBUG
    fclose(f);
    avcodec_close(c);
    av_free(c);
    av_frame_free(&frame);

    printf("\n");

    sprintf(msg, "decode done\n");
    __android_log_write(ANDROID_LOG_DEBUG, "jni_test", msg);

}

void AnnTestClass::DecodeVideo(const char *outfilename, const char *filename)
{
    DecodeVideo2(outfilename, filename);
}
