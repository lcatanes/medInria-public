/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medAbstractData.h>
#include <dtkCore/dtkAbstractView.h>

#include <medAbstractImageView.h>
#include <medAbstractViewCoordinates.h>

#include "v3dViewPluginExport.h"

class QMouseEvent;

class v3dViewPrivate;
class v3dViewObserver;
class vtkImageView;
class vtkImageView2D;
class vtkImageView3D;
class vtkRenderer;
class vtkRenderWindowInteractor;

/**
 * @class v3dView
 * @brief Concrete implementation of a medAbstractView using vtkinria3d's vtkImageView system.
 * v3dView stands for vtkinria3dView. It embeds in a QVTKWidget a visualization system for 2D
 * and 3D images.
 * Multiple overlays are supported: in 2D, overlays are layers of images displayed on top of
 * each others. Layer N is always drawn on top of layer N-1. Opacity, LUT and visibility can
 * be set per layer. In 3D, only VR is supported.
 **/

class V3DVIEWPLUGIN_EXPORT v3dView : public medAbstractImageView, public medAbstractViewCoordinates
{
    Q_OBJECT

public:
             v3dView();
    virtual ~v3dView();

    virtual QString description() const;
    virtual QString identifier() const;

    static bool registered();
    static QString s_identifier();

    // inherited from medAbstractView
    void reset();
    void clear();
    void update();
    
    void initializeInteractors();

    void *view();

    /**
     * Inputs the data to the vtkImageView2D/3D.
     * @param layer - specifies at which layer the image is inputed.
     * Layer N if always shown on top of layer N-1. By playing with
     * visibility and opacity, it is possible to show multiple images
     * on top of each others.
     */
    void setData(medAbstractData *data, int layer);

    void setSharedDataPointer(dtkSmartPointer<medAbstractData> data);

    /**
     * Inputs the data to the vtkImageView2D/3D instances.
     * Calling setData(data) will automatically position the data in
     * the next available layer. Example:
     * - first call  -> layer 0
     * - second call -> layer 1
     * ...
     * To set the data at a specific layer, call setData(data, layer).
     * To set the data to the first layer, call setData(data, 0).
     */
    void setData(medAbstractData *data);

    void *data();

    QWidget *receiverWidget();
    QWidget *widget();

    void close();

    // access method to internal members for v3dView**Interactor classes

    /**
     * Returns pointers to internal instances of vtkImageView2D/3D.
     */
    vtkImageView2D *view2d();
    vtkImageView3D *view3d();

    /**
     * Returns a pointer to the current view, being 2D or 3D.
     */
    vtkImageView *currentView();

    /**
     * Returns the vtkRenderWindowInteractor instance.
     */
    vtkRenderWindowInteractor *interactor();

    /**
     * Access methods to vtkRenderer members.
     */
    vtkRenderer *renderer2d();
    vtkRenderer *renderer3d();

    virtual QStringList getAvailableTransferFunctionPresets();
    virtual void getTransferFunctions( QList<double> & scalars,
				       QList<QColor> & colors );
    virtual void setTransferFunctions( QList<double> scalars,
				       QList<QColor > colors );
    virtual void setColorLookupTable( QList< double > scalars,
				      QList< QColor > colors );

    /**
     * Set/Get the visibility of the image at layer given by @param layer.
     */
    virtual bool visibility(int layer) const;

    /**
     * Set/Get the opacity of the image at layer given by @param layer.
     */
    virtual double opacity(int layer) const;

    /**
     * Returns the total number of layers of the vtkImageView* instance.
     */
    virtual int layerCount() const;

    /**
     * Removes an overlay given the layer id.
     */
    virtual void removeOverlay(int layer);
   // QString property(const QString& key, int layer) const;
   // using dtkAbstractObject::property;
    QString getLUT(int layer) const;
    QString getPreset(int layer) const;

    medAbstractViewCoordinates * coordinates();

    virtual medViewBackend * backend() const;

    void changeBounds (const double bounds[6], const int imageSize[3] = 0);

public slots:
    // inherited from medAbstractView
    void onPositionChanged  (const  QVector3D &position);
    void onZoomChanged      (double zoom);
    void onPanChanged       (const  QVector2D &pan);
    void onWindowingChanged (double level, double window);
    void onCameraChanged    (const  QVector3D &position,
                             const  QVector3D &viewup,
                             const  QVector3D &focal,
                             double parallelScale);

public slots:
    void play          (bool value);
    void onPropertySet         (const QString &key, const QString &value);
    void setOrientation           (const QString &value);
    void set3DMode                (const QString &value);
    void setRenderer              (const QString &value);
    void showScalarBar            (const bool &value);
    void showAxis                 (const bool &value);
    void showRuler                (const bool &value);
    void showAnnotations          (const bool &value);
    void setMouseInteraction      (const QString &value);
    void setCropping              (const bool &value);
    void setZoomMode              (const QString &value);
    void onClosablePropertySet    (const QString &value);
    void setDepthPeeling          (const bool &value);

public slots:
    void setSlider                          ( int value );
    void onZSliderValueChanged              (int value);

    void onMainWindowDeactivated();

public:
    void  enableInteraction();
    void disableInteraction();
    void bounds(float& xmin, float& xmax, float& ymin, float& ymax, float& zmin, float& zmax);
    void cameraUp(double *coordinates);
    void cameraPosition(double *coordinates);
    void cameraFocalPoint(double *coordinates);
    void setCameraPosition(double x, double y, double z);
    void setCameraClippingRange(double nearRange, double farRange);

    QString cameraProjectionMode();
    double cameraViewAngle();
    double cameraZoom();
    void setCurrentLayer(int layer);

public :
    // Satisfy medAbstractViewCoordinates API
    //! Convert from world coordinates to scene coordinates.
    virtual QPointF worldToDisplay( const QVector3D & worldVec ) const;
    //! Convert from scene coordinates to world coordinates.
    virtual QVector3D displayToWorld( const QPointF & scenePoint ) const;
    //! Get the view center vector in world space, the center of the slice for 2d views.
    virtual QVector3D viewCenter() const;
    //! Get the view plane normal vector in world space.
    virtual QVector3D viewPlaneNormal() const;
    //! Get the view plane up vector in world space.
    virtual QVector3D viewUp() const;
    //! Is the scene 2D (true) or 3D (false)
    virtual bool is2D() const;
    //! What is the thickness of the current slice (2D)
    virtual qreal sliceThickness() const;
    virtual qreal scale() const;

protected slots:
    void widgetDestroyed();

protected:
    virtual bool eventFilter(QObject * obj, QEvent * event);
private:

    template <typename IMAGE>
    bool SetViewInput(const char* type,medAbstractData* data,const int layer);
    bool SetView(const char* type,medAbstractData* data);
    template <typename IMAGE>
    bool SetViewInputWithConversion(const char* type,const char* newtype,medAbstractData* data,const int layer);

    v3dViewPrivate *d;

    friend class v3dViewObserver;
};

dtkAbstractView *createV3dView();


