/*
 * Copyright 2022-2023 Blueberry d.o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include "common.h"
#include <opendaq/device_impl.h>

#include "hbk/sys/eventloop.h"
#include "hbk/string/replace.h"
#include "jet/peerasync.hpp"

BEGIN_NAMESPACE_JET_MODULE

#define SELECTION_PROPERTY_RETURN_VALUE 0xAA // randomly chosen value that determinePropertyType() returns when it encounters SelectionProperty

class JetServer
{
public:
    static constexpr char jetStatePath[] = "/daq/JetModule/";
    static constexpr char globalIdString[] = "Global ID";
    static constexpr char typeString[] = "_type";

    explicit JetServer(const DevicePtr& device);
    ~JetServer();
    void publishJetStates();
    void updateJetState(const PropertyObjectPtr& propertyObject);

private:
    void createComponentJetState(const ComponentPtr& component);
    void createComponentListJetStates(const ListPtr<ComponentPtr>& componentList);

    void createJsonProperty(const ComponentPtr& component, const PropertyPtr& property);
    void createJsonProperties(const ComponentPtr& component);
    template <typename ValueType>
    void appendPropertyToJsonValue(const ComponentPtr& component, const std::string& propertyName, const ValueType& value);
    void appendMetadataToJsonValue(const ComponentPtr& component);
    void addJetState(const std::string& path);

    bool determineSelectionProperty(const PropertyPtr& property);

    void createCallbackForProperty(const PropertyPtr& property);

    DevicePtr rootDevice;

    Json::Value jsonValue;
    hbk::sys::EventLoop jet_eventloop; 
    hbk::jet::PeerAsync* jetPeer;
};


END_NAMESPACE_JET_MODULE