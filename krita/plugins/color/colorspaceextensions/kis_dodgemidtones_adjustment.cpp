/*
 *  SPDX-FileCopyrightText: 2013 Sahil Nagpal <nagpal.sahil01@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kis_dodgemidtones_adjustment.h"
#include <KoConfig.h>

#include <kis_debug.h>
#include <klocalizedstring.h>
#ifdef HAVE_OPENEXR
#include <half.h>
#endif

#include <KoColorConversions.h>
#include <KoColorModelStandardIds.h>
#include <KoColorSpace.h>
#include <KoColorSpaceTraits.h>
#include <KoColorTransformation.h>
#include <KoID.h>
 
template<typename _channel_type_, typename traits >
class KisDodgeMidtonesAdjustment : public KoColorTransformation
 {
    typedef traits RGBTrait;
    typedef typename RGBTrait::Pixel RGBPixel;

public:
    KisDodgeMidtonesAdjustment(){}

public:
    
    void transform(const quint8 *srcU8, quint8 *dstU8, qint32 nPixels) const override
    {
    	const RGBPixel* src = reinterpret_cast<const RGBPixel*>(srcU8);
        RGBPixel* dst = reinterpret_cast<RGBPixel*>(dstU8);
        float value_red, value_green, value_blue;
        const float factor(1.0/(1.0 + exposure));
        while(nPixels > 0) {

            value_red = pow((float)KoColorSpaceMaths<_channel_type_, float>::scaleToA(src->red), factor);
            value_green = pow((float)KoColorSpaceMaths<_channel_type_, float>::scaleToA(src->green), factor);
            value_blue = pow((float)KoColorSpaceMaths<_channel_type_, float>::scaleToA(src->blue), factor);
            
            dst->red = KoColorSpaceMaths< float, _channel_type_ >::scaleToA(value_red);
            dst->green = KoColorSpaceMaths< float, _channel_type_ >::scaleToA(value_green);
            dst->blue = KoColorSpaceMaths< float, _channel_type_ >::scaleToA(value_blue);
            dst->alpha = src->alpha;
            
            --nPixels;
            ++src;
            ++dst;
        }
    }

    QList<QString> parameters() const override
    {
    	QList<QString> list;
    	list << "exposure";
    	return list;
    }

    int parameterId(const QString& name) const override
    {
        if (name == "exposure")
        return 0;
        return -1;
    }

    void setParameter(int id, const QVariant& parameter) override
    {
        switch(id)
        {
        case 0:
            exposure = parameter.toDouble();
            break;
        default:
            ;
        }
    }
private:

    float exposure {0.0f};
};

 KisDodgeMidtonesAdjustmentFactory::KisDodgeMidtonesAdjustmentFactory()
    : KoColorTransformationFactory("DodgeMidtones")
{
}

QList< QPair< KoID, KoID > > KisDodgeMidtonesAdjustmentFactory::supportedModels() const
{
    QList< QPair< KoID, KoID > > l;
    l.append(QPair< KoID, KoID >(RGBAColorModelID , Integer8BitsColorDepthID));
    l.append(QPair< KoID, KoID >(RGBAColorModelID , Integer16BitsColorDepthID));
    l.append(QPair< KoID, KoID >(RGBAColorModelID , Float16BitsColorDepthID));
    l.append(QPair< KoID, KoID >(RGBAColorModelID , Float32BitsColorDepthID)); 
    return l;
}

KoColorTransformation* KisDodgeMidtonesAdjustmentFactory::createTransformation(const KoColorSpace* colorSpace, QHash<QString, QVariant> parameters) const
{
    KoColorTransformation * adj;
    if (colorSpace->colorModelId() != RGBAColorModelID) {
        dbgKrita << "Unsupported color space " << colorSpace->id() << " in KisDodgeMidtonesAdjustmentFactory::createTransformation";
        return 0;
    }
    if (colorSpace->colorDepthId() == Float32BitsColorDepthID) {
        adj = new KisDodgeMidtonesAdjustment< float, KoRgbTraits < float > >();
    }
#ifdef HAVE_OPENEXR
    else if (colorSpace->colorDepthId() == Float16BitsColorDepthID) {
        adj = new KisDodgeMidtonesAdjustment< half, KoRgbTraits < half > >();
    }
#endif
    else if(colorSpace->colorDepthId() == Integer16BitsColorDepthID) {
        adj = new KisDodgeMidtonesAdjustment< quint16, KoBgrTraits < quint16 > >();
    } else if(colorSpace->colorDepthId() == Integer8BitsColorDepthID) {
        adj = new KisDodgeMidtonesAdjustment< quint8, KoBgrTraits < quint8 > >();
    } else {
        dbgKrita << "Unsupported color space " << colorSpace->id() << " in KisDodgeMidtonesAdjustmentFactory::createTransformation";
        return 0;
    }
    adj->setParameters(parameters);
    return adj;
}
