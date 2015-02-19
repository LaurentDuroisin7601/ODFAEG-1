#ifndef ODFAEG_BOUNDING_POLYHEDRON_HPP
#define ODFAEG_BOUNDING_POLYHEDRON_HPP
#include <vector>
#include "../Math/vec2f.h"
#include "../Math/vec4.h"
#include "boundingVolume.h"
#include "../Math/ray.h"
/**
  *\namespace odfaeg
  * the namespace of the Opensource Development Framework Adapted for Every Games.
  */
namespace odfaeg {
     namespace physic {
        /**
          * \file boundingPolyhedron.h
          * \class BoudingPolyhedron
          * \brief Manage a bounding polyhedron for collision detection
          * \author Duroisin.L
          * \version 1.0
          * \date 1/02/2014
          *
          * Manage a bounding polyhedron for collision detection.
          *
          */
        class BoundingSphere;
        class BoundingEllipsoid;
        class BoundingBox;
        class OrientedBoundingBox;
        class BoundingPolyhedron : public BoundingVolume {
            public :
            BoundingPolyhedron();
            /**\fn BoundingPolyhedron()
            * \brief Default constructor : construct a bounding polyhedron. (with no points)
            */
            BoundingPolyhedron (math::Vec3f p1, math::Vec3f p2, math::Vec3f p3);
             /**\fn ~BoundingPolyhedron()
            * \brief destructor : delete all the points of the bounding polyhedron.
            */
            ~BoundingPolyhedron();
            /**\fn void addPoint(math::Vec3f *p)
            *  \param add a point to a polyhedron.
            */
            void addPoint(math::Vec3f p);
            /**\fn Vec2f getPoint(unsigned int index)
            *  \brief get the point of the polyhedron with the given index.
            *(0 = the index of the first point added, 1 = the index of the second, etc...
            * The index must be between 0 and the number of polyhedron's points - 1.
            *  \param the index of the point
            *  \return the point of the polyhedron at the given index.
            */
            math::Vec3f getPoint (unsigned int index);
            bool onIntersects (BaseInterface& interface) {
                return interface.intersects(*this);
            }
            bool onIntersects (BaseInterface& interface, math::Ray& ray, bool segment) {
                return interface.intersects(ray, segment);
            }
            bool onIntersects (BaseInterface& interface, math::Ray& ray, math::Vec3f& near, math::Vec3f& far) {
                return interface.intersectsWhere(ray, near, far);
            }
            std::unique_ptr<BoundingVolume> clone() {
                return std::make_unique<BoundingPolyhedron>(*this);
            }
            /**\fn bool intersects (BoundingSphere &bs)
            *  \brief check if the bounding polyhedron collides with the bounding sphere.
            *  \param the bounding sphere to test with.
            *  \return the result of the collision test.
            */
            bool intersects (BoundingSphere &bs);
            /**\fn bool intersects (BoundingEllipsoid &be)
            *  \brief check if the bounding polyhedron collides with the bounding ellipsoid.
            *  \param the bounding ellipsoid to test with.
            *  \return the result of the collision test.
            */
            bool intersects (BoundingEllipsoid &be);
            /**\fn bool intersects (BoundingBox &bx)
            *  \brief check if the bounding polyhedron collides with the bounding box.
            *  \param the bounding box to test with.
            *  \return the result of the collision test.
            */
            bool intersects (BoundingBox &bx);
            /**\fn bool intersects (OrientedBoundingBox &obx)
            *  \brief check if the bounding polyhedron collides with the oriented bounding box.
            *  \param the oriented bounding box to test with.
            *  \return the result of the collision test.
            */
            bool intersects (OrientedBoundingBox &obx);
            /**\fn bool intersects (BoundingPolyhedron &bp)
            *  \brief check if the bounding polyhedron collides with an other.
            *  \param the other bounding polyhedron to test with.
            *  \return the result of the collision test.
            */
            bool intersects (BoundingPolyhedron &bp);
            /**\fn bool isPointInside (math::Vec3f &point)
            *  \brief check if a given point is in the bounding polyhedron.
            *  \param the point to test in.
            *  \return the result of the collision test.
            */
            bool isPointInside (math::Vec3f point);
            /**\fn bool operator== (const BoundingPolyhedron &bp)
            *  \brief check if two bounding polyhedrons are equals.
            *  \param the other bounding polyhedron to test with.
            *  \return the result of the comparaison.
            */
            bool operator== (const BoundingPolyhedron &bs);
            /**\fn Vec2f getCenter()
            *  \brief return the center of the bounding polyhedron
            *  \return the center of the bounding polyhedron.
            */
            math::Vec3f getPosition();
            math::Vec3f getSize();
            math::Vec3f getCenter();
            std::vector<math::Vec3f> get3DNormals();
            std::vector<math::Vec3f> get2DNormals();
            std::vector<math::Vec3f> get3DBissectors();
            std::vector<math::Vec3f> get2DBissectors();
            std::vector<math::Vec3f> getPoints();
            /**\fn int nbPoints()
            *  \brief return the number of points of the bounding polyhedron
            *  \return the number of points of the bounding polyhedron.
            */
            int nbPoints ();
            bool intersects (math::Ray& ray, bool segment);
            bool intersectsWhere(math::Ray& ray, math::Vec3f& i1, math::Vec3f& i2);
            std::string getType() {
                return "BoundingPolygon";
            }
            template <typename Archive>
            void vtserialize(Archive & ar) {
                ar(points);
                ar(normals3D);
                ar(normals2D);
                ar(bissectors2D);
                ar(bissectors3D);
                ar(center);
                ar(size);
            }
            void move(math::Vec3f t);
            void scale(math::Vec3f s);
            void rotate(float angle, math::Vec3f r);
            private :
            /**\fn void computeCenter()
            *  \brief recompute the center of the bounding polyhedron. (When we add or remove points.)
            *
            */
            void computeVectors();
            std::vector<math::Vec3f> points; /**< The points of the polyhedron.*/
            std::vector<math::Vec3f> normals3D; /**< The perpendicular normals to the faces of the polygon*/
            std::vector<math::Vec3f> normals2D; /**< The perpendicular normals to the faces of the polygon*/
            std::vector<math::Vec3f> bissectors2D; /**< The bissectors of the polygon*/
            std::vector<math::Vec3f> bissectors3D;
            math::Vec3f center; /**< The center of the bounding polyhedron.*/
            math::Vec3f size;
        };
    }
}
#endif
