
// tetris2View.cpp : implementation of the Ctetris2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "tetris2.h"
#endif

#include "tetris2Doc.h"
#include "tetris2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctetris2View

IMPLEMENT_DYNCREATE(Ctetris2View, CView)

BEGIN_MESSAGE_MAP(Ctetris2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ctetris2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Ctetris2View construction/destruction

Ctetris2View::Ctetris2View() noexcept
{
	// TODO: add construction code here
	banco = Banco();

}

Ctetris2View::~Ctetris2View()
{
}

BOOL Ctetris2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// Ctetris2View drawing

void Ctetris2View::OnDraw(CDC* /*pDC*/)
{
	Ctetris2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CClientDC pdc(this);
	banco.vehinh(&pdc);
}


// Ctetris2View printing


void Ctetris2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ctetris2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ctetris2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ctetris2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Ctetris2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ctetris2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ctetris2View diagnostics

#ifdef _DEBUG
void Ctetris2View::AssertValid() const
{
	CView::AssertValid();
}

void Ctetris2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctetris2Doc* Ctetris2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctetris2Doc)));
	return (Ctetris2Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctetris2View message handlers
UINT capnhathinh(LPVOID pParam)
{
	int ran = 0;
	Ctetris2View* cview = (Ctetris2View*)pParam;
	CClientDC pdc(cview);
	cview->banco.capnhathinh(&pdc);
	return 0;
}
UINT capnhatgachroi(LPVOID pParam)
{
	int ran = 0;
	Ctetris2View* cview = (Ctetris2View*)pParam;
	
	cview->banco.capnhatgachroi();
	return 0;
}


void Ctetris2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (nChar == VK_SPACE) { // Sử dụng VK_SPACE thay vì 32 cho rõ ràng hơn
        if (!banco.dk) { // Kiểm tra xem game đã bắt đầu chưa
            batdaugame(); // Gọi hàm batdaugame() của bạn
            Invalidate(FALSE); // Gọi lại hàm vẽ để cập nhật giao diện
        }
    } else {
        banco.bamphimdichuyen(nChar); // Xử lý các phím khác như cũ
    }
    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int Ctetris2View::batdaugame()
{
	// TODO: Add your implementation code here.
	banco.batdaugame();
	
	AfxBeginThread(capnhatgachroi, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	AfxBeginThread(capnhathinh, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return 0;
}