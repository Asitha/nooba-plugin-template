#include "templateplugin.h"
#include <QtCore>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

TemplatePlugin::TemplatePlugin():
    windowTitle(tr("Template Plugin"))      // use a class member to define the window title as a practice
{
}

TemplatePlugin::~TemplatePlugin()
{
}

bool TemplatePlugin::procFrame( const cv::Mat &in, cv::Mat &out, ProcParams &params )
{
    Q_UNUSED(out)    // remove this line when params struct is used

    return true;
}

bool TemplatePlugin::init()
{
    // parameter creation should be done here
    return true;
}

bool TemplatePlugin::release()
{
    // resource created should be released here. Created parameter need not be released
    return true;
}

PluginInfo TemplatePlugin::getPluginInfo() const
{
    PluginInfo pluginInfo(
        "Template Plugin",
        0,
        1,
        "Plugin Description goes here",
        "Plugin Creator");
    return pluginInfo;
}

void TemplatePlugin::onIntParamChanged(const QString &varName, int val)
{

}

void TemplatePlugin::onDoubleParamChanged(const QString &varName, double val)
{

}

void TemplatePlugin::onStringParamChanged(const QString &varName, const QString &val)
{
}

void TemplatePlugin::onMultiValParamChanged(const QString &varName, const QString &val)
{
    if(tr("Viewer").compare(varName) == 0)
    {
        if(val.compare("Enable") == 0)
        {
            setFrameViewerVisibility(windowTitle, true);
        }
        else if(val.compare("Disable") == 0)
        {
            setFrameViewerVisibility(windowTitle, false);
        }
    }
}

void TemplatePlugin::onFilePathParamChanged(const QString &varName, const QString &path)
{
}

void TemplatePlugin::onLineParamUpdated(const QString &varName, const QString frameViewerTitle, QLine line)
{
}

QImage TemplatePlugin::convertToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    else if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img;
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}


// see qt4 documentation for details on the macro (Qt Assistant app)
// Mandatory  macro for plugins in qt4. Made obsolete in qt5
#if QT_VERSION < 0x050000
    Q_EXPORT_PLUGIN2(TemplatePlugin, TemplatePlugin);
#endif
