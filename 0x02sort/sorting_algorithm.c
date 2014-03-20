/**
  *  Copyright (C) 2014-03-21  Handsome Zhou
  */


void *bubble_sort(void *sort_data, int sort_data_len)
{
	int *psd=(int *)sort_data;
	int sd_len=sort_data_len;
	int sort_finish_flag=1;
	int i=0;
	int j=0;
	int tmp_data=0;

	for(i=0; i<sd_len-1; i++){
		sort_finish_flag=1;
		for(j=0; j<sd_len-1-i; j++){
			if(*(psd+j)>*(psd+j+1)){
				tmp_data=*(psd+j);
				*(psd+j)=*(psd+j+1);
				*(psd+j+1)=tmp_data;
				sort_finish_flag=0;
			}
		}
		if(1==sort_finish_flag){
			break;
		}
	}

	return psd;
}

