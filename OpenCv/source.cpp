#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<Windows.h>

using namespace cv;
using namespace std;

Point2f noktalar[] = { Point2f(268,516),Point2f(760,516),Point2f(1002,616),Point2f(16,616) };
Point2f donusum[] = { Point2f(0,0),Point2f(640,0),Point2f(640,480),Point2f(0,480) };
vector<int> serit;
Mat ilgili_bolge;
Mat sonuc;
int solKonum, sagKonum;
int pid;
void renk_donusumu(Mat giris) {
	Mat cikis;
	
	cvtColor(giris, giris, COLOR_BGR2GRAY);
	threshold(giris, giris, 120, 255, THRESH_BINARY);
	Canny(giris, giris,70,175);
	add(giris, cikis, sonuc);
	imshow("sonuc", sonuc);
}
void serit_bul() {
	serit.resize(640);
	serit.clear();
	for (int i = 0; i < 640; i++)
	{
		ilgili_bolge = sonuc(Rect(i, 150, 2, 100));
		divide(255, ilgili_bolge, ilgili_bolge);
		serit.push_back((int)(sum(ilgili_bolge)[0]));
	}
}
void serit_goster(Mat son) {
	vector<int>::iterator sol;
	sol = max_element(serit.begin(), serit.begin() + 150);
	solKonum = distance(serit.begin(), sol);
	vector<int>::iterator sag;
	sag = max_element(serit.begin()+350, serit.end());
	sagKonum = distance(serit.begin(), sag);
	line(son, Point(solKonum, 0), Point(solKonum, 480), Scalar(0, 156, 150), 2);
	line(son, Point(sagKonum, 0), Point(sagKonum, 480), Scalar(0, 156, 150), 2);
	imshow("serit tespiti", son);
}
void serit_merkez_bul(Mat son) {
	int seritMerkez = (sagKonum - solKonum) / 2 + solKonum;
	int kalibre = son.cols / 2 - 16;
	line(son, Point(seritMerkez, 0), Point(seritMerkez, 480), Scalar(0, 0, 255), 2);
	line(son, Point(kalibre, 0), Point(kalibre, 480), Scalar(0, 255, 0), 2);
	imshow("Son Hal", son);
}
int main() {
	VideoCapture serit("serit.mp4");
	if (!serit.isOpened()) cout << "Serit bulma islemi basarisiz!";
	else
	{
		while (true)
		{
			Mat oku;
			serit.read(oku);
			Mat pers = getPerspectiveTransform(noktalar, donusum);
			Mat son(480, 640, CV_8UC3);
			warpPerspective(oku, son, pers, son.size());
			renk_donusumu(son);
			serit_bul();
			serit_goster(son);
			serit_merkez_bul(son);
			stringstream yazi;
			yazi.str(" ");
			yazi.clear();
			yazi << "PID degeri:" << pid;
			putText(oku, yazi.str(), Point(150, 150), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 0), 2);

			//imshow("þerit kuþbakýþý", son);
			imshow("orj", oku);
			imshow("serit", son);
			if (waitKey(50) == 32) break;
			
				
			
		
		
		}
	}
	
	
}
