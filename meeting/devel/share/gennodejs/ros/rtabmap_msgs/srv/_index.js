
"use strict";

let DetectMoreLoopClosures = require('./DetectMoreLoopClosures.js')
let RemoveLabel = require('./RemoveLabel.js')
let PublishMap = require('./PublishMap.js')
let GetNodeData = require('./GetNodeData.js')
let SetGoal = require('./SetGoal.js')
let GetMap = require('./GetMap.js')
let LoadDatabase = require('./LoadDatabase.js')
let GetNodesInRadius = require('./GetNodesInRadius.js')
let GlobalBundleAdjustment = require('./GlobalBundleAdjustment.js')
let GetPlan = require('./GetPlan.js')
let CleanupLocalGrids = require('./CleanupLocalGrids.js')
let AddLink = require('./AddLink.js')
let ResetPose = require('./ResetPose.js')
let SetLabel = require('./SetLabel.js')
let ListLabels = require('./ListLabels.js')
let GetMap2 = require('./GetMap2.js')

module.exports = {
  DetectMoreLoopClosures: DetectMoreLoopClosures,
  RemoveLabel: RemoveLabel,
  PublishMap: PublishMap,
  GetNodeData: GetNodeData,
  SetGoal: SetGoal,
  GetMap: GetMap,
  LoadDatabase: LoadDatabase,
  GetNodesInRadius: GetNodesInRadius,
  GlobalBundleAdjustment: GlobalBundleAdjustment,
  GetPlan: GetPlan,
  CleanupLocalGrids: CleanupLocalGrids,
  AddLink: AddLink,
  ResetPose: ResetPose,
  SetLabel: SetLabel,
  ListLabels: ListLabels,
  GetMap2: GetMap2,
};
