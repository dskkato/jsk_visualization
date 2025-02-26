// -*- mode: c++ -*-
// Copyright (c) 2014, JSK Lab
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//  * Neither the name of the JSK Lab nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef JSK_RVIZ_PLUGIN_OVERLAY_UTIL_H_
#define JSK_RVIZ_PLUGIN_OVERLAY_UTIL_H_

#include <OgreHardwarePixelBuffer.h>
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
// see OgrePrerequisites.h
//#define OGRE_VERSION    ((OGRE_VERSION_MAJOR << 16) | (OGRE_VERSION_MINOR << 8) | OGRE_VERSION_PATCH)

// 1.10.xx
#if OGRE_VERSION < ((1 << 16) | (9 << 8) | 0)
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgrePanelOverlayElement.h>
#else
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreOverlayElement.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgrePanelOverlayElement.h>
#endif
#include <OgreMaterial.h>
#include <OgreSceneManager.h>
#include <OgreTexture.h>
#include <Overlay/OgreOverlay.h>

#include <QColor>
#include <QImage>

//#include <ros/ros.h>
#include <memory>
#include <rclcpp/rclcpp.hpp>

// #include "rviz_rendering/render_system.hpp"

namespace jsk_rviz_plugins
{
class OverlayObject;

class ScopedPixelBuffer
{
public:
  ScopedPixelBuffer(Ogre::HardwarePixelBufferSharedPtr pixel_buffer);
  virtual ~ScopedPixelBuffer();
  virtual Ogre::HardwarePixelBufferSharedPtr getPixelBuffer();
  virtual QImage getQImage(unsigned int width, unsigned int height);
  virtual QImage getQImage(OverlayObject & overlay);
  virtual QImage getQImage(unsigned int width, unsigned int height, QColor & bg_color);
  virtual QImage getQImage(OverlayObject & overlay, QColor & bg_color);

protected:
  Ogre::HardwarePixelBufferSharedPtr pixel_buffer_;

private:
};

// this is a class for put overlay object on rviz 3D panel.
// This class suppose to be instantiated in onInitialize method
// of rviz::Display class.

class OverlayObject
{
public:
  typedef std::shared_ptr<OverlayObject> Ptr;

  OverlayObject(const std::string & name);
  virtual ~OverlayObject();

  void prepareOverlays(Ogre::SceneManager * manager);
  virtual std::string getName();
  virtual void hide();
  virtual void show();
  virtual bool isTextureReady();
  virtual void updateTextureSize(unsigned int width, unsigned int height);
  virtual ScopedPixelBuffer getBuffer();
  virtual void setPosition(double left, double top);
  virtual void setDimensions(double width, double height);
  virtual bool isVisible();
  virtual unsigned int getTextureWidth();
  virtual unsigned int getTextureHeight();

protected:
  const std::string name_;
  Ogre::Overlay * overlay_;
  Ogre::PanelOverlayElement * panel_;
  Ogre::MaterialPtr panel_material_;
  Ogre::TexturePtr texture_;

private:
};

// Ogre::Overlay* createOverlay(std::string name);
// Ogre::PanelOverlayElement* createOverlayPanel(Ogre::Overlay* overlay);
// Ogre::MaterialPtr createOverlayMaterial(Ogre::Overlay* overlay);
}  // namespace jsk_rviz_plugins

#endif
