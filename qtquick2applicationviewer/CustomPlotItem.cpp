#include "CustomPlotItem.h"

#include <QDebug>

CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_CustomPlot( NULL )
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = NULL;
}

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();

    setupQuadraticDemo( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotItem::paint( QPainter* painter )
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        //m_CustomPlot->replot();
        m_CustomPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}

void CustomPlotItem::onCustomReplot()
{
    qDebug() << Q_FUNC_INFO;
    update();
}

void CustomPlotItem::setupQuadraticDemo( QCustomPlot* customPlot )
{
    // make top right axes clones of bottom left axes:
    QCPAxisRect* axisRect = customPlot->axisRect();
    QColor *back_color = new QColor(0,0,0);
    QBrush back_brush(*back_color,Qt::SolidPattern);
    customPlot ->setBackground(back_brush);

    // generate some data:
    QVector<double> x( 101 ), y( 101 );   // initialize with entries 0..100
    QVector<double> lx( 101 ), ly( 101 ); // initialize with entries 0..100
    QVector<double> lx2( 101 ), ly2( 101 ); // initialize with entries 0..100

    for(int div = 1; div < 100; ++div){
        float templength = (float)div*.01;
    //	vector<Port *> portsG;
        vector<Impedance *> impedancesG;
        vector<Intersection *> intersectionsG;


        //declaration of ports
    //	Port *p1 = new Port(1,std::complex<float>(50.0,0));
    //	Port *p2 = new Port(2,std::complex<float>(50.0,0));
    //	Port *p3 = new Port(3,std::complex<float>(50.0,0));

    //	p1->set_Node_Xid(1); //sets the intersection id
    //	p2->set_Node_Xid(2);
    //	p3->set_Node_Xid(3);

    //	portsG.push_back(p1);
    //	portsG.push_back(p2);
    //	portsG.push_back(p3);
        Impedance *p1 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(50.0,0),"P_1");
        Impedance *p2 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(50.0,0),"P_2");
        Impedance *p3 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(50.0,0),"P_3");

        Impedance *i1 = new Impedance((Impedance::IMPEDANCE_TYPES) 2, std::complex<float>(71.0,0),templength,"T_1"); //first tline
        Impedance *i2 = new Impedance((Impedance::IMPEDANCE_TYPES) 2, std::complex<float>(71.0,0),templength,"T_2"); //second tline
        Impedance *i3 = new Impedance((Impedance::IMPEDANCE_TYPES) 1, std::complex<float>(100.0,0),"T_3"); //first tline

        //vector<Port *> ports;
        //vector<Port *> ports2;
        //vector<Port *> ports3;
        //ports.push_back(p1);
        //ports2.push_back(p2);
        //ports3.push_back(p3);

        vector<Impedance *> X1impedances;
        vector<Impedance *> X2impedances;
        vector<Impedance *> X3impedances;

        X1impedances.push_back(p1);
        X2impedances.push_back(p2);
        X3impedances.push_back(p3);

        X1impedances.push_back(i1);
        X1impedances.push_back(i2);
        X2impedances.push_back(i1);
        X2impedances.push_back(i3);
        X3impedances.push_back(i2);
        X3impedances.push_back(i3);
        //X1impedances.push_back(i3);

        Intersection *X1 = new Intersection(1);
        Intersection *X2 = new Intersection(2);
        Intersection *X3 = new Intersection(3);

        //X1->set_Ports(ports);
        X1->set_Impedances(X1impedances);

        //X2->set_Ports(ports2);
        X2->set_Impedances(X2impedances);

        //X3->set_Ports(ports3);
        X3->set_Impedances(X3impedances);

        impedancesG.push_back(p1);
        impedancesG.push_back(p2);
        impedancesG.push_back(p3);
        impedancesG.push_back(i1);
        impedancesG.push_back(i2);
        impedancesG.push_back(i3);

        intersectionsG.push_back(X1);
        intersectionsG.push_back(X2);
        intersectionsG.push_back(X3);

        Circuit_Handler *ch = new Circuit_Handler(intersectionsG,impedancesG);

    //	ch->calc_S();
        //temp = i->get_Type();
        MatrixXcf R = ch->get_Port_Scattering_Abs();
        //cout << R << endl;


                            std::complex<float> S11 = R(0,0);
                            std::complex<float> S12 = R(0,1);
                            std::complex<float> S23 = R(1,2);


                            x[div] = (double) templength;
                            y[div] = (double) real(S11);
                            lx[div] = (double) templength;
                            ly[div] = (double) real(S12);
                            lx2[div] = (double) templength;
                            ly2[div] = (double) real(S23);

                         //   Sabs(m,n) = std::abs(j);
                         // filestream << std::real(j) << ",";



        //filestream << "\n";

        }
    // create graph and assign data to it:
    QCPItemText *textLabel = new QCPItemText(customPlot);
    customPlot->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("Wilkinson Divider");
    textLabel->setColor(QColor(255,255,255));
    textLabel->
    customPlot->addGraph();
    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 0 )->setData( x, y );
    customPlot->graph( 0 )->setName("S11");



    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::magenta ) );
    customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 1 )->setData( lx, ly );
    customPlot->graph( 1 )->setName("S12");

    customPlot->addGraph();
    customPlot->graph( 2 )->setPen( QPen( Qt::green ) );
    customPlot->graph( 2 )->setSelectedPen( QPen( Qt::yellow, 2 ) );
    customPlot->graph( 2 )->setData( lx2, ly2 );
    customPlot->graph( 2 )->setName("S23");





    // give the axes some labels:
    customPlot->xAxis->setLabel( "lambda" );
    customPlot->yAxis->setLabel( "Raw Mag( S )" );
    customPlot->xAxis->setLabelColor(QColor(255,255,255));
    customPlot->yAxis->setLabelColor(QColor(255,255,255));
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange( 0, 1 );
    customPlot->yAxis->setRange( 0, 1 );
    customPlot->xAxis->setTickLabelColor(QColor(255,255,255));
    customPlot->yAxis->setTickLabelColor(QColor(255,255,255));


    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );

    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
}
