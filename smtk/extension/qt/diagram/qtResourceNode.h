//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================
#ifndef smtk_extension_qtResourceNode_h
#define smtk_extension_qtResourceNode_h

#include "smtk/extension/qt/Exports.h"
#include "smtk/extension/qt/diagram/qtBaseObjectNode.h"

#include "smtk/common/TypeContainer.h"

#include "smtk/PublicPointerDefs.h"

#include <QGraphicsItem>
#include <QGraphicsScene>

class QAbstractItemModel;
class QGraphicsTextItem;
class QItemSelection;
class QTreeView;

namespace smtk
{
namespace resource
{
class PersistentObject;
}
namespace extension
{

/**\brief Rendering and interaction code for nodes that represent resources.
  *
  */
class SMTKQTEXT_EXPORT qtResourceNode : public qtBaseObjectNode
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem);
  Q_PROPERTY(QPointF pos READ pos WRITE setPos);
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation);

public:
  smtkSuperclassMacro(qtBaseObjectNode);
  smtkTypeMacro(smtk::extension::qtResourceNode);

  qtResourceNode(
    qtDiagramGenerator* generator,
    smtk::resource::PersistentObject* resource,
    QGraphicsItem* parent = nullptr);
  ~qtResourceNode() override = default;

  smtk::common::UUID nodeId() const override;
  smtk::resource::PersistentObject* object() const override;

  /// Get the bounding box of the node, which includes the border width and the label.
  QRectF boundingRect() const override;

  /// Handle renames, etc.
  void dataUpdated() override;

  smtk::resource::Resource* resource() const { return m_resource; }

protected:
  friend class ResourceNodeWidget;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

  /// Handle pointer hovers
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

  smtk::resource::Resource* m_resource{ nullptr };
};

} // namespace extension
} // namespace smtk

#endif // smtk_extension_qtResourceNode_h
