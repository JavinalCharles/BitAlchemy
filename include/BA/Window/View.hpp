#pragma once

#include <BA/Utilities/Angle.hpp>
#include <BA/Utilities/Rect.hpp>
#include <BA/Utilities/Vector2.hpp>
#include <BA/Utilities/Transform.hpp>

namespace ba {

class View {
public:

	/** @name ViewConstructors
	 * @brief Constructs a view.
	 * @param screenRect An rectangle representing a portion of the screen.
	 * @param worldTL The inital Top-Left coordinates of the world to be shown by this view.
	 * @param otherView A reference to another view
	 * 
	 */
	/**@{*/
	constexpr View() = default;
	constexpr View(const FloatRect& screenRect);
	constexpr View(const Vector2f& worldTL);
	constexpr View(const FloatRect& screenRect, const Vector2f& worldTL);
	constexpr View(const View& otherView);
	/**@}*/

	constexpr View& operator=(const View& otherView);

	/**
	 * Gets the center coordinate of the view in relation to 
	 * the world coordinate.
	 * @returns The center coordinates of the view relative to the world.
	 */
	constexpr Vector2f getCenter() const;

	/**
	 * Returns the total area of the viewport in the form of
	 * (width, height)
	 * @returns The View's area in Vector form {x = width, y = height}.
	 */
	constexpr Vector2i getArea() const;

	/**
	 * Returns the viewport, which is a FloattRect representing the View's actual position in the screen.
	 * @returns the viewport
	 */
	constexpr const FloatRect& getViewport() const;

	/**
	 * Returns the viewspace, which is a rectangle that the View could see on the world map.
	 * @returns the view space.
	 */
	constexpr FloatRect getViewSpace() const;

	/**
	 * Resizes the View area.
	 * @param area the new area of the viewport in the form {x = width, y = height}.
	 */
	void setArea(const Vector2f& area);

	/**
	 * Resizes the Viewport
	 * @param newViewport An IntRect that represents chunk of the screen.
	 */
	void setViewport(const FloatRect& newViewport);

	/**
	 * Moves the focus of the view relative to its current position in the world map. Should be used for side-scrolling effect.
	 */
	void move(const Vector2f& offset) const;

	/**
	 * Jumps the focus of the View to be centered on an specific coordinate relative to the world map.
	 * @param newCenter the new center coordinate of the view relative to the world map.
	 */
	void setCenter(const Vector2f& newCenter) const;

	/**
	 * Jumps the focus of the View so its top-left point is in a specific coordinate relative to the world map.
	 * @param newTL the new top-left coordinates of the view relative to the world map.
	 */
	void setTopLeft(const Vector2f& newTL) const;

	/**
	 * @brief maps the given rect in relation to this view.
	 * 
	 * This method accepts a rectangle oriented in world coordinates and transform it to a rectangle oriented more towards this view (i.e. screen coordinates).
	 * @param rect rectangle to be mapped.
	 * @return a rectangle mapped relatively to the view.
	**/
	constexpr FloatRect mapToView(const FloatRect& rect) const;

	/**
	 * @brief maps the given vector in relation to this view
	 * 
	 * @param coord vector to be mapped.
	 * @return a vector mapped to the view.
	**/
	constexpr Vector2f mapToView(const Vector2f& coord) const;

private:
	mutable Vector2f	m_viewTL{0.f, 0.f};
	FloatRect 			m_viewport{{0.f, 0.f}, {640.f, 480.f}};

}; // class View


constexpr View::View(const FloatRect& screenRect) :
	m_viewport(screenRect)
{
}

constexpr View::View(const Vector2f& worldTL) :
	m_viewTL(worldTL)
{
}

constexpr View::View(const FloatRect& screenRect, const Vector2f& worldTL) :
	m_viewTL(worldTL),
	m_viewport(screenRect)
{
}

constexpr View::View(const View& otherView) :
	m_viewTL(otherView.m_viewTL),
	m_viewport(otherView.m_viewport)
{

}

constexpr View& View::operator=(const View& otherView) {
	if (this != &otherView) {
		this->m_viewTL = otherView.m_viewTL;
		this->m_viewport = otherView.m_viewport;
	}
	return *this;
}

constexpr Vector2f View::getCenter() const {
	return m_viewTL + (m_viewport.getArea() / 2.f);
}

constexpr Vector2i View::getArea() const {
	return m_viewport.getArea();
}

constexpr const FloatRect& View::getViewport() const {
	return m_viewport;
}

constexpr FloatRect View::getViewSpace() const {
	return FloatRect(m_viewTL, m_viewport.getArea());
}

constexpr FloatRect View::mapToView(const FloatRect& rect) const {
	return FloatRect{
		mapToView({rect.l, rect.t}),
		{rect.w, rect.h}
	};
}

constexpr Vector2f View::mapToView(const Vector2f& coord) const {
	return coord - static_cast<Vector2f>(m_viewTL);
}


} // namespace ba