#include "FPSCounter.h"


void FPSCounter::calculate_fps()
{
	const auto current_time = std::chrono::system_clock::now();
	const std::chrono::duration<float> elapsed_seconds = current_time - last_frame_time_;
	last_frame_time_ = current_time;
	++frame_counter_;

	const auto frame_time = elapsed_seconds.count();
	elapsed_frame_time_ += frame_time;

	// update fps every half second
	if (elapsed_frame_time_ >= 0.5f) {

		average_fps_ = static_cast<float>(frame_counter_) / elapsed_frame_time_;
		emit emit_fps("FPS: " + fps_to_str());
		elapsed_frame_time_ = 0;
		frame_counter_ = 0;
	}
}

QString FPSCounter::fps_to_str() const
{
	QString fps_to_str{};
	fps_to_str.setNum(average_fps_, 'g', 3);
	return fps_to_str;
}
