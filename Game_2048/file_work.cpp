#include "file_work.h"

void file_4x4(int final_score)
{
	FILE* filelist;
	if (final_score >= 2048)
	{
		fopen_s(&filelist, "results/winner.txt", "a");
		fprintf_s(filelist, "Режим 4x4:\tКоличество набранных очков: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
	if (final_score < 2048)
	{
		fopen_s(&filelist, "results/looser.txt", "a");
		fprintf_s(filelist, "Режим 4x4:\tКоличество набранных очков: ");
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
		fprintf_s(filelist, "Режим 5x5:\tКоличество набранных очков: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
	if (final_score < 2048)
	{
		fopen_s(&filelist, "results/looser.txt", "a");
		fprintf_s(filelist, "Режим 5x5:\tКоличество набранных очков: ");
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
		fprintf_s(filelist, "Режим fast:\tКоличество набранных очков: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
	if (final_score < 2048)
	{
		fopen_s(&filelist, "results/looser.txt", "a");
		fprintf_s(filelist, "Режим fast:\tКоличество набранных очков: ");
		fprintf_s(filelist, "%d\n", final_score);
		fclose(filelist);
	}
}