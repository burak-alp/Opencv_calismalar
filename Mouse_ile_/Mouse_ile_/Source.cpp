#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

struct bolge {
	int baslangic;
	int basX;
	int basY;

	int sonX;
	int sonY;
	Rect kirpilmis_bolge;
	Mat alinan_bolge;
};
bolge dikdortgen;

void fonksiyon(int etkinlik, int x, int y, int flags, void* userdata) {
	if (etkinlik==EVENT_LBUTTONDOWN)
	{
		dikdortgen.basX = x;
		dikdortgen.basY = y;
		dikdortgen.baslangic = 1;
		cout << "Dikdotgenin ilk degerleri alindi. X degeri:" << dikdortgen.basX << "Y degeri:" << dikdortgen.basY << endl;

	}
	if (etkinlik==EVENT_LBUTTONUP)
	{
		dikdortgen.sonX = x;
		dikdortgen.sonY = y;
		cout << "Dikdotgenin son degerleri alindi. X degeri:" << dikdortgen.sonX << "Y degeri:" << dikdortgen.sonY << endl;
	}
	if (etkinlik==EVENT_MOUSEMOVE)
	{
		dikdortgen.sonX = x;
		dikdortgen.sonY = y;
		dikdortgen.kirpilmis_bolge = Rect(dikdortgen.basX, dikdortgen.basY, dikdortgen.sonX, dikdortgen.sonY);

	}
}	

int main() {
	Mat resim = imread("bitti.jpg");
	dikdortgen.baslangic = 0;
	while (true)
	{
		namedWindow("Goruntu", WINDOW_AUTOSIZE);
		setMouseCallback("Goruntu", fonksiyon, NULL);
		if (dikdortgen.baslangic!=0)
		{
			rectangle(resim, Rect(dikdortgen.basX, dikdortgen.basY, dikdortgen.sonX - dikdortgen.basX, dikdortgen.sonY - dikdortgen.basY),Scalar(200,120,3),2);
		}
		imshow("Goruntu", resim);
		waitKey(200);
	}

}


