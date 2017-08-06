//ぶっちゃけよくわかってない
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define _USE_MATH_DEFINES
#include<math.h>

#define WAVEDATASIZE	16000

int main(void) {
	FILE *fp;

	/***文字列"RIFF"の宣言・設定***/
	const char *s_riff = "RIFF";

	/***文字列"WAVE"の宣言・設定***/
	const char *s_wave = "WAVE";
	/***ファイルサイズWholeSizeの宣言***/
	int WholeSize;

	/***文字列"fmt "の宣言・設定***/
	const char *s_fmt = "fmt ";
	/***fmtチャンクサイズの宣言***/
	int FmtChunkSize;
	/***↓フォーマットID:FmtIDを宣言・設定***/
	short FmtId = 1;
	/***↓チャネル数Channelを宣言・設定***/
	short Channel = 1;
	/***↓サンプリングレートSamplingRateを宣言・設定***/
	int SamplingRate = 8000;
	/***↓データ速度DataVelocityを宣言***/
	int DataVelocity;
	/***↓ブロックサイズBlockSizeを宣言・設定***/
	short BlockSize;
	/***↓サンプル単位ビット数を設定***/
	short Bps = 16;

	/***文字列"data"の設定***/
	const char *s_data = "data";
	/***↓dataチャンクサイズを宣言***/
	int DataChunkSize;
	/***↓波形データ配列WaveDataを宣言***/
	short WaveData[WAVEDATASIZE];

	int i, chk;

	/***↓データ速度DataVelocityを設定***/
	DataVelocity = SamplingRate*Bps / 8 * Channel;

	/***↓ブロックサイズBlockSizeを設定***/
	BlockSize = Bps / 8 * Channel;

	/***↓fmtチャンクサイズFmtchunkSizeを設定***/
	FmtChunkSize =
		sizeof(FmtId)
		+ sizeof(Channel)
		+ sizeof(SamplingRate)
		+ sizeof(DataVelocity)
		+ sizeof(BlockSize)
		+ sizeof(Bps);

	/***↓dataチャンクサイズDataChunkSizeを設定***/
	DataChunkSize = WAVEDATASIZE*BlockSize;

	/***↓ファイルサイズWholeSizeを設定***/
	WholeSize = strlen(s_wave)
		+ strlen(s_fmt)
		+ sizeof(FmtChunkSize)
		+ FmtChunkSize
		+ strlen(s_data)
		+ sizeof(DataChunkSize)
		+ DataChunkSize;

	/***波形データWaveDataの設定***/
	for (i = 0;i<WAVEDATASIZE;i++) {
		WaveData[i] = (short)(SHRT_MAX*sin(2 * M_PI*1000.0*((double)i) / (double)(SamplingRate)));
	}

	fp = fopen("pcm-8000Hz-1c-2byte-1000Hz-2sec.wav", "wb");
	if (fp == NULL) {
		printf("Cannot open File\n");
		exit(1);
	}

	/***↓"RIFF"のファイル出力***/
	chk = fwrite(s_riff, sizeof(s_riff[0]), strlen(s_riff), fp);
	if (chk<strlen(s_riff)) {
		printf("Write Error for s_riff\n");
		exit(1);
	}

	/***↓WholeSizeのファイル出力***/
	chk = fwrite(&WholeSize, sizeof(WholeSize), 1, fp);
	if (chk<1) {
		printf("Write Error for WholeSize\n");
		exit(1);
	}

	/***↓"WAVE"のファイル出力***/
	chk = fwrite(s_wave, sizeof(s_wave[0]), strlen(s_wave), fp);
	if (chk<strlen(s_wave)) {
		printf("Write Error for s_wave\n");
		exit(1);
	}

	/***ここからfmtチャンクのファイル出力***/

	/***↓"fmt "のファイル出力***/
	chk = fwrite(s_fmt, sizeof(s_fmt[0]), strlen(s_fmt), fp);
	if (chk<strlen(s_fmt)) {
		printf("Write Error for s_fmt\n");
		exit(1);
	}

	/***↓fmtチャンクサイズFmtChunkSizeのファイル出力***/
	chk = fwrite(&FmtChunkSize, sizeof(FmtChunkSize), 1, fp);
	if (chk<1) {
		printf("Write Error for FmtChunkSize\n");
		exit(1);
	}

	/***↓フォーマットID:FmtIdのファイル出力***/
	chk = fwrite(&FmtId, sizeof(FmtId), 1, fp);
	if (chk<1) {
		printf("Write Error for FmtId\n");
		exit(1);
	}

	/***↓チャネル数Channelのファイル出力***/
	chk = fwrite(&Channel, sizeof(Channel), 1, fp);
	if (chk<1) {
		printf("Write Error for Channel\n");
		exit(1);
	}

	/***↓サンプリングレートSamplingRateのファイル出力***/
	chk = fwrite(&SamplingRate, sizeof(SamplingRate), 1, fp);
	if (chk<1) {
		printf("Write Error for SamplingRate\n");
		exit(1);
	}

	/***↓データ速度DataVelocityのファイル出力***/
	chk = fwrite(&DataVelocity, sizeof(DataVelocity), 1, fp);
	if (chk<1) {
		printf("Write Error for DataVelocity\n");
		exit(1);
	}


	/***↓ブロックサイズBlockSizeのファイル出力***/
	chk = fwrite(&BlockSize, sizeof(BlockSize), 1, fp);
	if (chk<1) {
		printf("Write Error for BlockSize\n");
		exit(1);
	}

	/***↓サンプル単位ビット数Bpsのファイル出力***/
	chk = fwrite(&Bps, sizeof(Bps), 1, fp);
	if (chk<1) {
		printf("Write Error for Bps\n");
		exit(1);
	}

	/***ここまでfmtチャンクのファイル出力***/
	/***ここからdataチャンクのファイル出力***/

	/***↓"data"のファイル出力***/
	chk = fwrite(s_data, sizeof(s_data[0]), strlen(s_data), fp);
	if (chk<strlen(s_data)) {
		printf("Write Error for s_data\n");
		exit(1);
	}

	/***↓dataチャンクサイズDataChunkSizeのファイル出力***/
	chk = fwrite(&DataChunkSize, sizeof(DataChunkSize), 1, fp);
	if (chk<1) {
		printf("Write Error for DataChunkSize\n");
		exit(1);
	}

	/***↓波形データWaveDataのファイル出力***/
	chk = fwrite(WaveData, sizeof(WaveData[0]), sizeof(WaveData) / sizeof(WaveData[0]), fp);
	if (chk<sizeof(WaveData) / sizeof(WaveData[0])) {
		printf("Write Error for WaveData[%d]\n", i);
		exit(1);
	}

	/***ここまでdataチャンクのファイル出力***/

	fclose(fp);
	return 0;
}
