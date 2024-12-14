#include "pch.h"
#include "Banco.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

Banco::Banco()
{
	PlaySound(_T("C:\\Users\\nanh pc\\Downloads\\tetris200\\pianos-by-jtwayne-7-174717.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	diem = 0;
	level = 1;
	line = 0;
	tocdo = 1;
	dk = 0;
	int d = 40;
	pg = NULL;
	khungve = Hcnmau(XDAU, YDAU, XDAU + RONG, YDAU + CAO, 500, 600, 650);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0;j < 12;j++)
		{
			ds[i][j] = Oco(XDAU + j * d, YDAU + i * d, XDAU + j * d + d, YDAU + i * d + d, 255, 255, 255 );
		}
	}

}

void Banco::vehinh(CClientDC* pdc)
{
	// Tạo đối tượng phông chữ tùy chỉnh cho điểm và level
	CFont font;
	font.CreateFont(
		24,                        // Chiều cao phông chữ
		0,                         // Chiều rộng ký tự
		0,                         // Góc nghiêng của ký tự
		0,                         // Góc nghiêng của dòng cơ sở
		FW_BOLD,                   // Độ đậm của phông (FW_BOLD = đậm)
		FALSE,                     // Không nghiêng
		FALSE,                     // Không gạch chân
		FALSE,                     // Không gạch chéo
		DEFAULT_CHARSET,           // Bộ ký tự mặc định
		OUT_DEFAULT_PRECIS,        // Độ chính xác đầu ra
		CLIP_DEFAULT_PRECIS,       // Độ chính xác cắt
		DEFAULT_QUALITY,           // Chất lượng mặc định
		DEFAULT_PITCH | FF_SWISS,  // Dạng phông (FF_SWISS = không chân)
		_T("Arial")                // Tên phông chữ
	);

	// Lưu phông hiện tại và áp dụng phông mới
	CFont* pOldFont = pdc->SelectObject(&font);

	// Vẽ khung chính
	khungve = Hcnmau(XDAU, YDAU, XDAU + RONG, YDAU + CAO, 150, 150, 150);
	khungve.vehinh(pdc);

	// Hiển thị điểm và cấp độ
	CString strdiem, strlevel, strline;
	
	strdiem.Format(_T("SCORE: %d"), diem);
	strlevel.Format(_T("LEVEL: %d"), level);
	strline.Format(_T("Line: %d"),line);
	//strLine.Fort("Line: %d");

	// Tạo khung cho Score
	CRect scoreRect(XDAU + RONG + 30, YDAU + 30, XDAU + RONG + 220, YDAU + 80);
	pdc->Draw3dRect(scoreRect, RGB(0, 0, 0), RGB(255, 255, 255)); // Khung 3D
	pdc->TextOutW(XDAU + RONG + 40, YDAU + 40, strdiem);          // Văn bản Score

	// Tạo khung cho Level
	CRect levelRect(XDAU + RONG + 30, YDAU + 100, XDAU + RONG + 220, YDAU + 150);
	pdc->Draw3dRect(levelRect, RGB(0, 0, 0), RGB(255, 255, 255)); // Khung 3D
	pdc->TextOutW(XDAU + RONG + 40, YDAU + 110, strlevel);        // Văn bản Level 

	CRect lineRect(XDAU + RONG + 30, YDAU + 30, XDAU + RONG + 220, YDAU + 80);
	pdc->Draw3dRect(lineRect, RGB(0, 0, 0), RGB(255, 255, 255)); // Khung 3D
	pdc->TextOutW(XDAU + RONG + 40, YDAU + 200, strline);  // Văn bản line
	
	// Kiểm tra xem trò chơi đã bắt đầu chưa, nếu chưa thì hiển thị dòng "Press Space to start"
	//PlaySound(_T("C:\\Users\\ADMIN\\Downloads\\batdau (1).wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	if (dk == 0 && thua == 0) {
		CString strstart;
		
		strstart.Format(_T("Press Space to start "));
		
		// Vẽ nền cho dòng chữ để tránh viền hoặc kẻ chồng lên
		CRect startRect(XDAU + 120, YDAU + CAO / 2 - 50, XDAU + 400, YDAU + CAO / 2 + 10);
		pdc->FillSolidRect(startRect, RGB(150, 150, 150));  // Màu nền đen

		// Tạo phông chữ mới cho dòng "Press Space to start"
		CFont startFont;
		startFont.CreateFont(
			24,                        // Chiều cao phông chữ
			0,                         // Chiều rộng ký tự
			0,                         // Góc nghiêng của ký tự
			0,                         // Góc nghiêng của dòng cơ sở
			FW_BOLD,                   // Độ đậm của phông (FW_BOLD = đậm)
			FALSE,                     // Không nghiêng
			FALSE,                     // Không gạch chân
			FALSE,                     // Không gạch chéo
			DEFAULT_CHARSET,           // Bộ ký tự mặc định
			OUT_DEFAULT_PRECIS,        // Độ chính xác đầu ra
			CLIP_DEFAULT_PRECIS,       // Độ chính xác cắt
			DEFAULT_QUALITY,           // Chất lượng mặc định
			DEFAULT_PITCH | FF_SWISS,  // Dạng phông (FF_SWISS = không chân)
			_T("Arial")                // Tên phông chữ
		);

		// Áp dụng phông mới cho dòng chữ
		pdc->SelectObject(&startFont);
		pdc->SetTextColor(RGB(255, 255, 255));  // Màu chữ trắng
		pdc->TextOutW(XDAU + 120, YDAU + CAO / 2 - 20, strstart);  // Vẽ dòng "Press Space to start"
	}

	// Vẽ các khối gạch
	if (pg)
		pg->vehinh(pdc);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 12; j++)
			ds[i][j].vehinh(pdc);

	// Hiển thị thông báo Game Over (vẽ sau cùng để không bị che)
	//PlaySound(_T("C:\\Users\\ADMIN\\Downloads\\coin-recieved-230517.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	if (thua == 1) {
		CString strthua;
		strthua.Format(_T("GAME OVER"));
		
		pdc->SetTextColor(RGB(255, 0, 0)); // Đặt màu chữ đỏ
		pdc->TextOutW(XDAU + 120, YDAU + CAO / 2 - 50, strthua);
	}

	// Khôi phục lại phông và màu chữ cũ
	//pdc->SelectObject(pOldFont);
}




void Banco::capnhathinh(CClientDC* pdc)
{
	while (dk == 1)
	{
		vehinh(pdc);
		Sleep(50);
	}
	if (thua == 1)
	{
		CString strthua;
		strthua.Format(_T("Game Over"));
		PlaySound(_T("C:\\Users\\nanh pc\\Downloads\\tetris200\\ketthuc (1).wav"), NULL, SND_FILENAME | SND_ASYNC);
		pdc->TextOutW(XDAU + 120, YDAU + CAO / 2 - 50, strthua);
	}
}

void Banco::khoitaogach()
{
	int t = 0;
	t = rand() % 4;
	//tam gan t=0
	//t = 1;
	if (t == 0)
	{
		pg = new Gachvuong(XDAU + RONG / 2 - D, YDAU - 3 * D, 0, 255, 0, XDAU, YDAU);
	}
	if (t == 1)//khoi tao gach thang
	{
		pg = new Gachthang(XDAU + RONG / 2 - D, YDAU - 3 * D, 255, 255, 0, XDAU, YDAU);
	}
	if (t == 2)//khoi tao gach thang
	{
		pg = new GachT(XDAU + RONG / 2 - D, YDAU - 3 * D, 0, 255, 255, XDAU, YDAU);
	}
	if (t == 3)//khoi tao gach thang
	{
		pg = new GachL(XDAU + RONG / 2 - D, YDAU - 3 * D, 255, 0, 255, XDAU, YDAU);
	}

}

void Banco::capnhatgachroi()
{
	while (dk == 1)
	{
		if (pg)
		{
			int luutru = 0;
			if (pg->getYmax() < khungve.y2)
			{
				pg->dichxuong();
				int i, j{}, k;
				int d = 40;
				for (k = 0;k < 4;k++)
				{
					i = (pg->gach[k].y2 - YDAU) / d - 1;
					j = (pg->gach[k].x2 - XDAU) / d - 1;
					if (ds[i][j].trangthai == 1 && /*i >= 0 &&*/ j >= 0)
					{
						pg->dichlen();
						luutru = 1;
						break;
					}
				}
			}
			else
			{
				luutru = 1;
			}
			if(luutru==1)
			{
				//neu ko dich xuong duoc thi ghi nhan thong tin vao dsoco
				int i, j{}, k;
				int d = 40;
				for (k = 0;k < 4;k++)
				{
					i = (pg->gach[k].y2 - YDAU) / d-1;
					j = (pg->gach[k].x2 - XDAU) / d-1;
					if (i >= 0 && j >= 0)
					{
						ds[i][j].trangthai = 1;
						ds[i][j].r = pg->r;
						ds[i][j].g = pg->g;
						ds[i][j].b = pg->b;
					}
				}
				//kiem tra co tinh diem va xoa gach dc hay khong
				kiemtralaydiem();
				// kiem tra thua
				if (pg->getYmin() < khungve.y1)
				{
					thua = 1;
					dk = 0;
				}

				//tao gach moi
				khoitaogach();
			}
			Sleep(500-tocdo);
		}

	}
	
}

void Banco::batdaugame()
{

	dk = 1;
	khoitaogach();
	//capnhatgachroi();
}

void Banco::bamphimdichuyen(UINT nchar)
{
	if (dk == 0)
		return;
	if (nchar == 39)//dich phai
	{
		if (pg->getXmax() < khungve.x2)
		{
			pg->dichphai();
			if (cothedichchuyen() == 0)
				pg->dichtrai();
		}
		
	}
	else
		if (nchar == 37)//quatrai
		{
			if (pg->getXmin() > khungve.x1)
			{
				pg->dichtrai();
				if (cothedichchuyen() == 0)
					pg->dichphai();

			}
		}
		else
			if (nchar == 40)//di xuong
			{
				if (pg->getYmax() < khungve.y2)
				{
					pg->dichxuong();
					if (cothedichchuyen() == 0)
						pg->dichlen();
					else
						diem += 1; // Cộng 1 điểm mỗi lần nhấn phím xuống

				}
			
				
			}
			else 
				if (nchar == 38)//xoay hinh
				{
					pg->xoayhinh();
					if (cothedichchuyen() == 0)
						pg->traxoayhinh();
				}
}

int Banco::cothedichchuyen()
{
	//neu ko dich xuong duoc thi ghi nhan thong tin vao dsoco
	int i, j{}, k;
	int d = 40;
	for (k = 0;k < 4;k++)
	{
		i = (pg->gach[k].y2 - YDAU) / d - 1;
		j = (pg->gach[k].x2 - XDAU) / d - 1;
		if (/*i >= 0 &&*/ j >= 0 && i < 20 && j < 12)
		{
			if (ds[i][j].trangthai == 1)
				return 0;

		}
		else
			return 0;
	}
	return 1;
}

int Banco::kiemtrathua()
{
	return 0;
}

int Banco::kiemtralaydiem()
{
	int i = 0;
	int j = 0;
	int cot = 12;
	int hang = 20;
	int mdiem = 0;
	int mline = 0;
	int tong = 0;
	int sohangxoa = 0; // Biến đếm số hàng bị xóa

	for (i = 0; i < hang; i++)
	{
		tong = 0;
		for (j = 0; j < cot; j++)
		{
			tong = tong + ds[i][j].trangthai;
		}
		if (tong == cot)
		{
			sohangxoa++; // Tăng số hàng bị xóa
		}
	}

	// Tính điểm dựa trên số hàng bị xóa
	if (sohangxoa == 1)
		mdiem = 100;
	else if (sohangxoa == 2)
		mdiem = 300;
	else if (sohangxoa == 3)
		mdiem = 500;
	else if (sohangxoa == 4)
		mdiem = 700;

	diem += mdiem;

	if (sohangxoa == 1)
		mline = 1;
	else if (sohangxoa == 2)
		mline = 2;
	else if (sohangxoa == 3)
		mline = 3;
	else if (sohangxoa == 4)
		mline = 4;

	line += mline; 
	

	// Kiểm tra và cập nhật level

	int newLevel = diem / 300 + 1;
	if (newLevel > level) // Level tăng
	{
		level = newLevel;
		tocdo += 35; // Tăng tốc độ rơi
	}
	int newline = line;
	
	if (newline > line)
	{
		line = newline;
		
	}
	// Xóa các dòng bị xóa và cập nhật lại bảng
	for (i = 0; i < hang; i++)
	{
		tong = 0;
		for (j = 0; j < cot; j++)
		{
			tong = tong + ds[i][j].trangthai;
		}

		if (tong == cot)
		{
			// Xóa hàng bằng cách dời các dòng trên xuống
			int k = i;
			int m = 0;
			for (k = i; k > 0; k--)
				for (m = 0; m < cot; m++)
				{
					ds[k][m].trangthai = ds[k - 1][m].trangthai;
					ds[k][m].r = ds[k - 1][m].r;
					ds[k][m].g = ds[k - 1][m].g;
					ds[k][m].b = ds[k - 1][m].b;
				}
			k = 0;
			for (m = 0; m < cot; m++)
			{
				ds[k][m].trangthai = 0;
				ds[k][m].r = 255;
				ds[k][m].g = 255;
				ds[k][m].b = 255;
			}
			i--; // Lùi lại để kiểm tra dòng mới thay thế
		}
	}
	return 0;
}

