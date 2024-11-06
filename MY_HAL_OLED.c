/*
对OLED发送单个命令。
uint8_t Command: 发送的十六进制命令。
*/
void MY_OLED_Command(uint8_t Command)
{
	uint8_t Temp[2] = {0x00, Command};
	HAL_I2C_Master_Transmit(&hi2c1, OLED_address, Temp, 2, 1000);
}


/*
对OLED发送多个命令。
uint8_t Command[]: 发送的十六进制命令的数组，请不要搞错数据类型。
int Num: 数组长度。
*/
void MY_OLED_CommandM(uint8_t Command[], int Num)
{
	uint8_t Temp[Num+1];
	Temp[0] = 0x00;
	for (int ii=0; ii<Num; ii++)
	{
		Temp[ii+1] = Command[ii];
	}
	HAL_I2C_Master_Transmit(&hi2c1, OLED_address, Temp, Num+1, 1000);
}


/*
对OLED发送单个数据，请注意是数据而不是命令。
uint8_t Data: 发送的十六进制数据。
*/
void MY_OLED_Data(uint8_t Data)
{
	uint8_t Temp[2] = {0x40, Data};
	HAL_I2C_Master_Transmit(&hi2c1, OLED_address, Temp, 2, 1000);
}


/*
对OLED发送多个数据。
uint8_t Data[]: 发送的十六进制数据数组。
int i: 数组长度。
*/
void MY_OLED_DataM(uint8_t Data[], int Num)
{
	uint8_t Temp[Num+1];
	Temp[0] = 0x40;
	for (int ii=0; ii<Num; ii++)
	{
		Temp[ii+1] = Data[ii];
	}
	HAL_I2C_Master_Transmit(&hi2c1, OLED_address, Temp, Num+1, 1000);
}


/*
设置OLED的指针，跟标准库的原理一致。
uint8_t x: 指针的X轴参数，取值 0 ~ 128 。
uint8_t y: 指针的Y轴参数，取值 0 ~ 8 。
*/
void MY_OLED_SetCursor(uint8_t x, uint8_t y)
{
	uint8_t Temp[3] = {0xB0|y, 0x10|((x&0xF0)>>4), 0x00|(x&0x0F)};
	MY_OLED_CommandM(Temp, 3);
}


/*
用单个数据填充整个屏幕，一般用于清屏或显示白屏。
uint8_t data: 十六进制数据，如果想清屏取值 0x00 ,白屏取值 0xFF 。
*/
void MY_OLED_Full(uint8_t data)
{
	uint8_t i, Temp[128];
	for(i=0; i<128; i++)
	{
		Temp[i] = data;
	}
	for(i=0; i<8; i++)
	{
		MY_OLED_SetCursor(0, i);
		MY_OLED_DataM(Temp, 128);
	}
}


/*
显示图形，请配合取字模软件。
uint8_t data[]: 图形的数据数组。
int _Long: 图形的长度，取值 0 ~ 128 。
int _Hight: 图形的高度（=图形高度的像素/8），取值 0 ~ 8 。
int _X: 图形原点X轴参数，取值 0 ~ 128 。
int _Y: 图形原点Y轴参数，取值 0 ~ 8 。
*/
void MY_OLED_ShowP(uint8_t data[], int _Long, int _Hight, int _X, int _Y)
{
	for(uint8_t y1=0, Temp[_Long]; y1<_Hight; y1++)
	{
		for(int x1=0; x1<_Long; x1++)
		{
			Temp[x1] = data[x1+y1*_Long];
		}
		MY_OLED_SetCursor(_X, _Y+y1);
		MY_OLED_DataM(Temp, _Long);
	}
}


/*
就是清屏，好玩封装一下。
*/
void MY_OLED_Clear(void)
{  
	MY_OLED_Full(0x00);
}


/*
OLED初始化，请在使用其他函数前先使用此函数初始化OLED。
*/
void MY_OLED_Init(void)
{
	uint8_t DA[23] = {0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x30, 0xA4, 0xA6, 0x8D, 0x14, 0xAF};
	MY_OLED_CommandM(DA, 23);
	MY_OLED_Full(0);
}
