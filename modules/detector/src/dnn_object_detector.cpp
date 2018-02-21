#include "dnn_tracker_cpp/detector/dnn_object_detector.h"
#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/draw.h"

namespace dnn {

static
bool
is_low_probability_object(const core::bbox_t box, const target_object& target) {
  return (box.prob < target.probability);
}

static
std::vector<core::bbox_t>::iterator&
erase_unvalid_object(std::vector<core::bbox_t>& boxes,
                     std::vector<core::bbox_t>::iterator& box,
                     const object_names& object_names,
                     const target_objects& targets) {

  auto target = targets.find(object_names[*box]);
  if (target == targets.end()) {
    box = boxes.erase(box);
    return box;
  }
  else {

    if (target->erase_low_probability_objects &&
        is_low_probability_object(*box, *target)) {
      box = boxes.erase(box);
      return box;
    }

    ++box;
  }

  return box;
}

static
std::vector<core::bbox_t>&
erase_unvalid_objects(std::vector<core::bbox_t>& boxes,
                      const object_names& object_names,
                      const target_objects& targets) {

  if (boxes.empty()) {
    return boxes;
  }

  for (auto box = boxes.begin(); box != boxes.end();) {
    box = erase_unvalid_object(boxes, box, object_names, targets);
  }

  return boxes;
}

}


namespace dnn {

dnn_object_detector::
dnn_object_detector(std::tstring config_path,
                    std::tstring weight_path,
                    cv::Size detection_area,
                    int _frame_story,
                    float _threshold) :
  object_names(),
  checker(region::distance(detection_area_.width)),
  tracker(),
  frame_story(_frame_story),
  threshold(_threshold),
  detector_(std::to_string(config_path),
            std::to_string(weight_path)),
  detection_area_(detection_area) {}

bool
dnn_object_detector::
init(const std::tstring& filename,
     const target_objects &_targets) {

  bool ret = true;

  ret &= load_object_names(filename);

  if (!_targets.empty()) {
    set_target_objects(_targets);
    ret &= true;
  }

  return ret;
}

bool
dnn_object_detector::
load_object_names(const std::tstring& filename) {
  return object_names.load(filename);
}

void
dnn_object_detector::
set_target_objects(const target_objects &_targets) {
  checker.targets(_targets);
}

target_objects&
dnn_object_detector::
get_target_objects() {
  return checker.targets();
}



/*******************************************************************************
 main function
*******************************************************************************/

detection_info
dnn_object_detector::
detect(cv::Mat &src, cv::Size init_size) {

  //darknet detector
  auto tracked_objs = detector_.detect(src, init_size, [this](std::vector<core::bbox_t>& objs) {
    objs = erase_unvalid_objects(objs, object_names, checker.targets());
  });

  //wrapper detector
  auto boundary_boxes = region::make_boundaryboxes(tracked_objs);
  auto objects = tracker.tracking(boundary_boxes, object_names, checker.targets());

  auto now = std::chrono::system_clock::now();
  bool found_target = checker.judge_detection_targets(objects, object_names);

  return detection_info(objects, now, found_target);
  //return detection_info();
}

}



