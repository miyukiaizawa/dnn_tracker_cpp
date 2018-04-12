#pragma once
#ifndef __YOLO_V2_DETECTOR_H__
#define __YOLO_V2_DETECTOR_H__
#include "opencv2\opencv.hpp"
#include "opencv2\core\ocl.hpp"
#include "opencv2\dnn.hpp"
#include <vector>
#include <istream>

struct bbox_t {
  int x;
  int y;
  int width;
  int height;
  int obj_id;
  int track_id;
  float prob;
  int count;
};

class yolo_v2_detector {
public:

  yolo_v2_detector(std::string _cfg_file, std::string _weight_file, int _gpu_id = 0) :
    cfg_file(_cfg_file),
    weight_file(_weight_file),
    gpu_id(_gpu_id) {
    net = cv::dnn::readNetFromDarknet(cfg_file, weight_file);
  }

  std::vector<bbox_t> detect_resized(cv::InputArray src, cv::Size init_size, float thresh = 0.2, bool use_mean = false) {
    auto detection_boxes = detect(src, thresh, use_mean);

    cv::cuda::GpuMat img = src.getGpuMat();
    float wk = (float)init_size.width / img.cols;
    float hk = (float)init_size.height / img.rows;

    for (auto &box : detection_boxes) {
      box.x *= wk;
      box.width *= wk;
      box.y *= hk;
      box.height *= hk;
    }
    return detection_boxes;
  }

  std::vector<bbox_t> detect(cv::InputArray src, float thresh = 0.2, bool use_mean = false) {

    std::vector<bbox_t> bbox_vec;
    cv::cuda::GpuMat frame = src.getGpuMat();
    cv::Mat blob_src;
    frame.download(blob_src);

    cv::Mat input_blob = cv::dnn::blobFromImage(blob_src, 1 / 255.F, cv::Size(416, 416), cv::Scalar(),
 true, false);
    net.setInput(input_blob);
    cv::UMat gpu_detection_mat;
    net.forward(gpu_detection_mat, "detection_out");;
    cv::Mat detection_mat = gpu_detection_mat.getMat(cv::ACCESS_RW);

    std::vector<double> layers_timings;
    double tick_freq = cv::getTickFrequency();
    time_ms = net.getPerfProfile(layers_timings) / tick_freq * 1000;



    for (int index = 0; index < detection_mat.rows; index++) {

      const int probability_index = 5;
      const int probability_size = detection_mat.cols - probability_index;
      float *prob_array_ptr = &detection_mat.at<float>(index, probability_index);

      size_t object_class = std::max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
      float confidence = detection_mat.at<float>(index, (int)object_class + probability_index);

      if (confidence > thresh) {
        auto cx = detection_mat.at<float>(index, 0) * frame.cols;
        auto cy = detection_mat.at<float>(index, 1) * frame.rows;
        auto width = detection_mat.at<float>(index, 2) * frame.cols;
        auto height = detection_mat.at<float>(index, 3) * frame.rows;

        auto x = std::max((double)0, (cx - width / 2.));
        auto y = std::max((double)0, (cy - height / 2.));

        cv::Rect object(x, y, width, height);

        bbox_t bbox;
        bbox.x = object.x;
        bbox.y = object.y;
        bbox.width = object.width;
        bbox.height = object.height;
        bbox.obj_id = object_class;
        bbox.track_id = 0;
        bbox.count = 1;
        bbox.prob = confidence;

        bbox_vec.push_back(bbox);

      }

    }
    return bbox_vec;
  }

  bool load_object_name(std::string filepath) {
    std::ifstream class_name_file(filepath);
    if (class_name_file.is_open()) {
      std::string class_name = "";
      while (std::getline(class_name_file, class_name))
        class_names.push_back(class_name);
    }
    return true;
  }

  double time_ms;
  cv::dnn::Net net;
  cv::String cfg_file;
  cv::String weight_file;
  std::vector<std::string> class_names;

  std::deque<std::vector<bbox_t>> prev_boxs;
  int gpu_id = 0;

};

#endif //__YOLO_V2_DETECTOR_H__
