// Copyright 1996-2020 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WB_X3D_STREAMING_SERVER_HPP
#define WB_X3D_STREAMING_SERVER_HPP

#include "WbStreamingServer.hpp"

#include <QtCore/QHash>

class WbX3dStreamingServer : public WbStreamingServer {
  Q_OBJECT

public:
  WbX3dStreamingServer();

private slots:
  void propagateNodeAddition(WbNode *node) override;
  void propagateNodeDeletion(WbNode *node);
  void start(int port) override;
  void stop() override;
  void sendUpdatePackageToClients() override;
  virtual void processTextMessage(QString);

private:
  void create(int port) override;
  void onSimulationReset() override;
  void sendTcpRequestReply(const QString &requestedUrl, QTcpSocket *socket) override;
  void sendWorldToClient(QWebSocket *client) override;
  void sendWorldStateToClient(QWebSocket *client, const QString &state) const;
  void startX3dStreaming(QWebSocket *client);
  void generateX3dWorld();
  void newWorld() override;
  void deleteWorld() override;

  QString mX3dWorld;
  QHash<QString, QString> mX3dWorldTextures;
  double mX3dWorldGenerationTime;
  QString mX3dWorldReferenceFile;

  qint64 mLastUpdateTime;
};

#endif
