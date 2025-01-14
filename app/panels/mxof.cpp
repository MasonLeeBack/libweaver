#include "mxof.h"

#include <QLabel>

using namespace si;

MxOfPanel::MxOfPanel(QWidget *parent) :
  Panel(parent)
{
  int row = 0;

  layout()->addWidget(new QLabel(tr("Object Count")), row, 0);

  obj_count_edit_ = new QSpinBox();
  obj_count_edit_->setMinimum(0);
  obj_count_edit_->setMaximum(INT_MAX);
  layout()->addWidget(obj_count_edit_, row, 1);

  row++;

  list_ = new QListWidget();
  layout()->addWidget(list_, row, 0, 1, 2);

  FinishLayout();
}

void MxOfPanel::OnOpeningData(si::Chunk *chunk)
{
  const Data &offsets_bytes = chunk->data("Offsets");
  const u32 *offsets = reinterpret_cast<const u32*>(offsets_bytes.data());
  size_t offset_count = offsets_bytes.size() / sizeof(u32);

  obj_count_edit_->setValue(chunk->data("Count"));

  for (size_t i=0; i<offset_count; i++) {
    QString addr = QStringLiteral("0x%1").arg(offsets[i], 8, 16, QChar('0'));

    list_->addItem(QStringLiteral("%1: %2").arg(QString::number(i), addr));
  }
}

void MxOfPanel::OnClosingData(si::Chunk *chunk)
{
  list_->clear();
}
