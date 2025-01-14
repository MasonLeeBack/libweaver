#include "mxhd.h"

#include <QLabel>

using namespace si;

MxHdPanel::MxHdPanel(QWidget *parent)
  : Panel{parent}
{
  int row = 0;

  auto version_layout = new QHBoxLayout();
  layout()->addLayout(version_layout, row, 0, 1, 2);

  version_layout->addWidget(new QLabel(tr("Major Version")));

  major_version_edit_ = new QSpinBox();
  major_version_edit_->setMinimum(0);
  major_version_edit_->setMaximum(UINT16_MAX);
  version_layout->addWidget(major_version_edit_);

  version_layout->addWidget(new QLabel(tr("Minor Version")));

  minor_version_edit_ = new QSpinBox();
  minor_version_edit_->setMinimum(0);
  minor_version_edit_->setMaximum(UINT16_MAX);
  version_layout->addWidget(minor_version_edit_);

  row++;

  layout()->addWidget(new QLabel(tr("Buffer Alignment")), row, 0);

  buffer_alignment_edit_ = new QSpinBox();
  buffer_alignment_edit_->setMinimum(0);
  buffer_alignment_edit_->setMaximum(INT_MAX); // Technically this is UINT32_MAX but QSpinBox only supports int
  layout()->addWidget(buffer_alignment_edit_, row, 1);

  row++;

  layout()->addWidget(new QLabel(tr("Buffer Count")), row, 0);

  buffer_count_edit_ = new QSpinBox();
  buffer_count_edit_->setMinimum(0);
  buffer_count_edit_->setMaximum(INT_MAX); // Technically this is UINT32_MAX but QSpinBox only supports int
  layout()->addWidget(buffer_count_edit_, row, 1);

  FinishLayout();
}

void MxHdPanel::OnOpeningData(Chunk *chunk)
{
  si::u32 version = chunk->data("Version");
  uint16_t major_ver = version >> 16;
  uint16_t minor_ver = version;

  major_version_edit_->setValue(major_ver);
  minor_version_edit_->setValue(minor_ver);
  buffer_alignment_edit_->setValue(chunk->data("BufferSize"));
  buffer_count_edit_->setValue(chunk->data("BufferCount"));
}

void MxHdPanel::OnClosingData(Chunk *chunk)
{
  chunk->data("Version") = (major_version_edit_->value() << 16 | (minor_version_edit_->value() & 0xFFFF));
  chunk->data("BufferSize") = buffer_alignment_edit_->value();
  chunk->data("BufferCount") = buffer_count_edit_->value();
}
