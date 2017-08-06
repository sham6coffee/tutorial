#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define _USE_MATH_DEFINES
#include<math.h>

#define WAVEDATASIZE	16000

int main(void) {
	FILE *fp;

	/***������"RIFF"�̐錾�E�ݒ�***/
	const char *s_riff = "RIFF";

	/***������"WAVE"�̐錾�E�ݒ�***/
	const char *s_wave = "WAVE";
	/***�t�@�C���T�C�YWholeSize�̐錾***/
	int WholeSize;

	/***������"fmt "�̐錾�E�ݒ�***/
	const char *s_fmt = "fmt ";
	/***fmt�`�����N�T�C�Y�̐錾***/
	int FmtChunkSize;
	/***���t�H�[�}�b�gID:FmtID��錾�E�ݒ�***/
	short FmtId = 1;
	/***���`���l����Channel��錾�E�ݒ�***/
	short Channel = 1;
	/***���T���v�����O���[�gSamplingRate��錾�E�ݒ�***/
	int SamplingRate = 8000;
	/***���f�[�^���xDataVelocity��錾***/
	int DataVelocity;
	/***���u���b�N�T�C�YBlockSize��錾�E�ݒ�***/
	short BlockSize;
	/***���T���v���P�ʃr�b�g����ݒ�***/
	short Bps = 16;

	/***������"data"�̐ݒ�***/
	const char *s_data = "data";
	/***��data�`�����N�T�C�Y��錾***/
	int DataChunkSize;
	/***���g�`�f�[�^�z��WaveData��錾***/
	short WaveData[WAVEDATASIZE];

	int i, chk;

	/***���f�[�^���xDataVelocity��ݒ�***/
	DataVelocity = SamplingRate*Bps / 8 * Channel;

	/***���u���b�N�T�C�YBlockSize��ݒ�***/
	BlockSize = Bps / 8 * Channel;

	/***��fmt�`�����N�T�C�YFmtchunkSize��ݒ�***/
	FmtChunkSize =
		sizeof(FmtId)
		+ sizeof(Channel)
		+ sizeof(SamplingRate)
		+ sizeof(DataVelocity)
		+ sizeof(BlockSize)
		+ sizeof(Bps);

	/***��data�`�����N�T�C�YDataChunkSize��ݒ�***/
	DataChunkSize = WAVEDATASIZE*BlockSize;

	/***���t�@�C���T�C�YWholeSize��ݒ�***/
	WholeSize = strlen(s_wave)
		+ strlen(s_fmt)
		+ sizeof(FmtChunkSize)
		+ FmtChunkSize
		+ strlen(s_data)
		+ sizeof(DataChunkSize)
		+ DataChunkSize;

	/***�g�`�f�[�^WaveData�̐ݒ�***/
	for (i = 0;i<WAVEDATASIZE;i++) {
		WaveData[i] = (short)(SHRT_MAX*sin(2 * M_PI*1000.0*((double)i) / (double)(SamplingRate)));
	}

	fp = fopen("pcm-8000Hz-1c-2byte-1000Hz-2sec.wav", "wb");
	if (fp == NULL) {
		printf("Cannot open File\n");
		exit(1);
	}

	/***��"RIFF"�̃t�@�C���o��***/
	chk = fwrite(s_riff, sizeof(s_riff[0]), strlen(s_riff), fp);
	if (chk<strlen(s_riff)) {
		printf("Write Error for s_riff\n");
		exit(1);
	}

	/***��WholeSize�̃t�@�C���o��***/
	chk = fwrite(&WholeSize, sizeof(WholeSize), 1, fp);
	if (chk<1) {
		printf("Write Error for WholeSize\n");
		exit(1);
	}

	/***��"WAVE"�̃t�@�C���o��***/
	chk = fwrite(s_wave, sizeof(s_wave[0]), strlen(s_wave), fp);
	if (chk<strlen(s_wave)) {
		printf("Write Error for s_wave\n");
		exit(1);
	}

	/***��������fmt�`�����N�̃t�@�C���o��***/

	/***��"fmt "�̃t�@�C���o��***/
	chk = fwrite(s_fmt, sizeof(s_fmt[0]), strlen(s_fmt), fp);
	if (chk<strlen(s_fmt)) {
		printf("Write Error for s_fmt\n");
		exit(1);
	}

	/***��fmt�`�����N�T�C�YFmtChunkSize�̃t�@�C���o��***/
	chk = fwrite(&FmtChunkSize, sizeof(FmtChunkSize), 1, fp);
	if (chk<1) {
		printf("Write Error for FmtChunkSize\n");
		exit(1);
	}

	/***���t�H�[�}�b�gID:FmtId�̃t�@�C���o��***/
	chk = fwrite(&FmtId, sizeof(FmtId), 1, fp);
	if (chk<1) {
		printf("Write Error for FmtId\n");
		exit(1);
	}

	/***���`���l����Channel�̃t�@�C���o��***/
	chk = fwrite(&Channel, sizeof(Channel), 1, fp);
	if (chk<1) {
		printf("Write Error for Channel\n");
		exit(1);
	}

	/***���T���v�����O���[�gSamplingRate�̃t�@�C���o��***/
	chk = fwrite(&SamplingRate, sizeof(SamplingRate), 1, fp);
	if (chk<1) {
		printf("Write Error for SamplingRate\n");
		exit(1);
	}

	/***���f�[�^���xDataVelocity�̃t�@�C���o��***/
	chk = fwrite(&DataVelocity, sizeof(DataVelocity), 1, fp);
	if (chk<1) {
		printf("Write Error for DataVelocity\n");
		exit(1);
	}


	/***���u���b�N�T�C�YBlockSize�̃t�@�C���o��***/
	chk = fwrite(&BlockSize, sizeof(BlockSize), 1, fp);
	if (chk<1) {
		printf("Write Error for BlockSize\n");
		exit(1);
	}

	/***���T���v���P�ʃr�b�g��Bps�̃t�@�C���o��***/
	chk = fwrite(&Bps, sizeof(Bps), 1, fp);
	if (chk<1) {
		printf("Write Error for Bps\n");
		exit(1);
	}

	/***�����܂�fmt�`�����N�̃t�@�C���o��***/
	/***��������data�`�����N�̃t�@�C���o��***/

	/***��"data"�̃t�@�C���o��***/
	chk = fwrite(s_data, sizeof(s_data[0]), strlen(s_data), fp);
	if (chk<strlen(s_data)) {
		printf("Write Error for s_data\n");
		exit(1);
	}

	/***��data�`�����N�T�C�YDataChunkSize�̃t�@�C���o��***/
	chk = fwrite(&DataChunkSize, sizeof(DataChunkSize), 1, fp);
	if (chk<1) {
		printf("Write Error for DataChunkSize\n");
		exit(1);
	}

	/***���g�`�f�[�^WaveData�̃t�@�C���o��***/
	chk = fwrite(WaveData, sizeof(WaveData[0]), sizeof(WaveData) / sizeof(WaveData[0]), fp);
	if (chk<sizeof(WaveData) / sizeof(WaveData[0])) {
		printf("Write Error for WaveData[%d]\n", i);
		exit(1);
	}

	/***�����܂�data�`�����N�̃t�@�C���o��***/

	fclose(fp);
	return 0;
}