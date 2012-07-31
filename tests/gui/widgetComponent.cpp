#include "widget_component.hpp"
#include "data/io_factory.hpp"
#include "qt_widget/qt_widget.hpp"
#include <QApplication>

int main(int argc,char **argv)
{
	QApplication app(argc, argv);
	isis::util::slist paths;
	paths.push_back(argv[1]);
	isis::glance::widget::QtWidget *w = new isis::glance::widget::QtWidget;

	isis::glance::data::IOFactory::setUseProposedDataType(true);
	isis::glance::data::IOFactory::load( *w, paths );
	
	isis::glance::qt4::WidgetComponent wc(0,w);
	w->show();
	return app.exec();
}