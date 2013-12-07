#ifndef TEMPLATEPLUGIN_H
#define TEMPLATEPLUGIN_H

#include "templateplugin_global.h"
#include "noobapluginapi.h"

#include <QObject>

class TEMPLATEPLUGIN_EXPORT TemplatePlugin: public NoobaPluginAPI
{
    Q_OBJECT
    Q_INTERFACES(NoobaPluginAPI)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "nooba.plugins.qt5.template-plugin" FILE "templatePlugin.json")
#endif

public:
    TemplatePlugin();
    ~TemplatePlugin();

    bool procFrame(const cv::Mat &in, cv::Mat &out, ProcParams &params);
    bool init();
    bool release();
    PluginInfo getPluginInfo() const;

public slots:

    /**
     * These functions will be called when the relevant parameters are changed by the
     * user.
     */
    void onIntParamChanged(const QString& varName, int val);
    void onDoubleParamChanged(const QString& varName, double val);
    void onStringParamChanged(const QString& varName, const QString& val);
    void onMultiValParamChanged(const QString& varName, const QString& val);
    void onFilePathParamChanged(const QString &varName, const QString &path);
    void onLineParamUpdated(const QString &varName, const QString frameViewerTitle, QLine line);


private:

    /**
     * @brief convertToQImage
     * @param mat   expects the cv::Mat pixel layout to be RGB. NoobaVSS provides it input
     *              cv::Mat frames in RGB format.
     * @return      returns a copy of QImage
     */
    QImage convertToQImage(const cv::Mat &mat);

    const QString           windowTitle;

};

#endif // TEMPLATEPLUGIN_H
