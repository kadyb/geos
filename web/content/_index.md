---
title: "GEOS"
date: 2021-10-04T14:13:20-07:00
draft: false
geekdocNav: true
---

GEOS is a C/C++ library for spatial computational geometry of the sort generally used by "geographic information systems" software. GEOS is a core dependency of [PostGIS](https://postgis.net), [QGIS](https://qgis.org), [GDAL](https://gdal.org), and [Shapely](https://shapely.readthedocs.io/en/stable/project.html).

If you need support using the GEOS library or would like to get involved in the community
check out our [Community Support]({{< ref "community/support" >}}) page.

## Capabilities

Spatial Model and Functions

* **Geometries**: Point, LineString, Polygon, MultiPoint, MultiLineString, MultiPolygon, GeometryCollection
* **Predicates**: Intersects, Touches, Disjoint, Crosses, Within, Contains, Overlaps, Equals, Covers
* **Operations**: Union, Distance, Intersection, Symmetric Difference, Convex Hull, Envelope, Buffer, Simplify, Polygon Assembly, Valid, Area, Length,
* Prepared geometries (pre-spatially indexed)
* STR spatial index
* OGC Well Known Text (WKT) and Well Known Binary (WKB) encoders and decoders.

## API Features

* [C API]({{< ref "usage/c_api" >}}) (provides long-term API and ABI stability)
* [C++ API]({{< ref "usage/cpp_api" >}}) (will likely change across versions)
* Thread safety (using the [reentrant API]({{<ref "usage/c_api/#reentrantthreadsafe-api" >}}))

## License

GEOS is [open source software](https://opensource.com/resources/what-open-source) available under the terms of [GNU Lesser General Public License](http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html) (LGPL).

## Citation

To cite GEOS in publications use:

> GEOS contributors (2021). GEOS computational geometry library. Open Source Geospatial Foundation. URL https://libgeos.org/.

A BibTeX entry for LaTeX users is
```
@Manual{,
  title = {{GEOS} coordinate transformation software library},
  author = {{GEOS contributors}},
  organization = {Open Source Geospatial Foundation},
  year = {2021},
  url = {https://libgeos.org/},
}
```
## Relationship to JTS

GEOS started as a direct port to C++ of the
[JTS Topology Suite](https://github.com/locationtech/jts/) (JTS),
and remains tightly bound to that project. Most core algorithms have
been developed in JTS and ported to GEOS when complete.

The projects share testing data.  This helps to ascertain when failures
are caused by differences in implementation (GEOS fails and JTS does not)
and when they are caused by algorithm (both libraries fail).


## Governance

The GEOS project is run by a
[Project Steering Committee]({{< ref "psc" >}}) made up of developers
and contributors to the project and is a project of
[OSGeo](https://www.osgeo.org/projects/geos/). We strive to keep our day-to-day interactions collegial and welcoming within a basic [Code of Conduct]({{< ref "coc" >}}).
