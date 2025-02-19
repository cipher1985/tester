/*
 *  SPDX-FileCopyrightText: 2021 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KoResourceCacheInterface.h"
#include <KisStaticInitializer.h>

KIS_DECLARE_STATIC_INITIALIZER {
    qRegisterMetaType<KoResourceCacheInterfaceSP>("KoResourceCacheInterfaceSP");
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QMetaType::registerEqualsComparator<KoResourceCacheInterfaceSP>();
#endif
}

KoResourceCacheInterface::~KoResourceCacheInterface()
{

}

void KoResourceCacheInterface::setRelatedResourceCookie(RelatedResourceCookie cookie)
{
    m_cookie = cookie;
}

KoResourceCacheInterface::RelatedResourceCookie KoResourceCacheInterface::relatedResourceCookie() const
{
    return m_cookie;
}
