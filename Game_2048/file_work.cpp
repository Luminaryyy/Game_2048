#include "file_work.h"

void file_4x4(int final_score)
{
	FILE* filelist;
	if (final_score >= 2048)
	{
		fopen_s(&filelist, "results/winner.txt", "a");
		fprintf_s(filelist, "����� 4x4:\t���������� ��������� �����: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
	if (final_score < 2048)
	{
		fopen_s(&filelist, "results/looser.txt", "a");
		fprintf_s(filelist, "����� 4x4:\t���������� ��������� �����: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
}

void file_5x5(int final_score)
{
	FILE* filelist;
	if (final_score >= 2048)
	{
		fopen_s(&filelist, "results/winner.txt", "a");
		fprintf_s(filelist, "����� 5x5:\t���������� ��������� �����: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
	if (final_score < 2048)
	{
		fopen_s(&filelist, "results/looser.txt", "a");
		fprintf_s(filelist, "����� 5x5:\t���������� ��������� �����: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
}

void file_fast(int final_score)
{
	FILE* filelist;
	if (final_score >= 2048)
	{
		fopen_s(&filelist, "results/winner.txt", "a");
		fprintf_s(filelist, "����� fast:\t���������� ��������� �����: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
	if (final_score < 2048)
	{
		fopen_s(&filelist, "results/looser.txt", "a");
		fprintf_s(filelist, "����� fast:\t���������� ��������� �����: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
}