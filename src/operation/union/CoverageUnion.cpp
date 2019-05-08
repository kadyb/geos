/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2019 Daniel Baston <dbaston@gmail.com>
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <geos/operation/union/CoverageUnion.h>

#include <geos/geom/GeometryCollection.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/LineString.h>
#include <geos/geom/Polygon.h>
#include <geos/operation/polygonize/Polygonizer.h>
#include <geos/util/IllegalArgumentException.h>

namespace geos {
namespace operation {
namespace geounion {

using geos::geom::Geometry;
using geos::geom::LineSegment;
using geos::geom::LineString;
using geos::geom::Polygon;
using geos::geom::GeometryCollection;
using geos::geom::GeometryFactory;
using geos::operation::polygonize::Polygonizer;

void CoverageUnion::extractSegments(const Geometry* geom) {
    const Polygon* p = dynamic_cast<const Polygon*>(geom);
    if (p != nullptr) {
        extractSegments(p);
    } else {
        auto gc = dynamic_cast<const GeometryCollection*>(geom);
        if (gc == nullptr) {
            throw geos::util::IllegalArgumentException("Unhandled geometry type in CoverageUnion.");
        }

        for (size_t i = 0; i < gc->getNumGeometries(); i++) {
            extractSegments(gc->getGeometryN(i));
        }
    }
}

void CoverageUnion::extractSegments(const Polygon* p) {
    const LineString* ring = p->getExteriorRing();

    extractSegments(ring);
    for (size_t i = 0; i < p->getNumInteriorRing(); i++) {
        extractSegments(p->getInteriorRingN(i));
    }


}

void CoverageUnion::extractSegments(const LineString* ls) {
    auto coords = ls->getCoordinatesRO();

    if (coords->isEmpty())
        return;

    for (size_t i = 1; i < coords->size(); i++) {
        LineSegment segment{coords->getAt(i), coords->getAt(i-1)};
        segment.normalize();

       if (!segments.erase(segment)) {
           segments.emplace(std::move(segment));
       }
    }
}

std::unique_ptr<Geometry> CoverageUnion::polygonize(const GeometryFactory* gf) {
    Polygonizer p{true};

    // Create a vector to manage the lifecycle of a geometry corresponding to each line segment.
    // Polygonizer needs these to stay alive until it does its work.
    std::unique_ptr<std::vector<std::unique_ptr<Geometry>>> segment_geoms;
    segment_geoms.reset(new std::vector<std::unique_ptr<Geometry>>());
    segment_geoms->reserve(segments.size());

    for (const LineSegment& segment : segments) {
        auto seg_geom = segment.toGeometry(*gf);
        p.add(static_cast<Geometry*>(seg_geom.get()));
        segment_geoms->emplace_back(std::move(seg_geom));
    }

    auto polygons{p.getPolygons()};
    segment_geoms.reset();

    if (polygons->size() == 1) {
        return std::unique_ptr<Geometry>((*polygons)[0].release());
    }

    std::unique_ptr<std::vector<Geometry*>> geoms{new std::vector<Geometry*>{polygons->size()}};
    for (size_t i = 0; i < polygons->size(); i++) {
        (*geoms)[i] = (*polygons)[i].release();
    }

    return std::unique_ptr<Geometry>{gf->createMultiPolygon(geoms.release())};
}

std::unique_ptr<geom::Geometry> CoverageUnion::Union(const geom::Geometry* geom) {
    CoverageUnion cu;
    cu.extractSegments(geom);
    return cu.polygonize(geom->getFactory());
}

}
}
}
