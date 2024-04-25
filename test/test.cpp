
pair<Mat, map<int, int>> find_Line(const Mat& image, double threshold) {
	int width = image.cols;
	int height = image.rows;
	vector<int> significantRows;
	map<int, int> rowMapping;

	for (int y = 0; y < height; ++y) {
		int whiteCount = 0;
		for (int x = 0; x < width; ++x) {
			if (image.at<uchar>(y, x) == 255) {
				whiteCount++;
			}
		}
		double ratio = static_cast<double>(whiteCount) / width;
		if (ratio > threshold) {
			significantRows.push_back(y);
		}
	}

	Mat result = Mat::zeros(image.size(), image.type());
	int newRow = 0;
	for (int row : significantRows) {
		image.row(row).copyTo(result.row(newRow));
		rowMapping[row] = newRow++;
	}

	return { result, rowMapping };
}




int main() {

	string path = "D:/Ai_h/img/2";

	vector<cv::String> filenames;
	cv::glob(path, filenames);

	Ald_measure* measure();
	auto PInv = std::make_shared<Ald_measure>();

	while (true)
	{
		for (const auto& filename : filenames)

		{
			Mat src = imread(filename, 0);
			//Mat result(src.size(), CV_8UC1);
			Mat img_temp1, img_temp2, img_temp3;
			Ald_measure* measure();

			//shared_ptr<Ald_measure>PInv(measure());



			auto [rearranged, rowMapping] = find_Line(src, 0.03);







			for (int y = 0; y < rearranged.cols; y++) {
				int startX = -1;

				for (int x = 0; x < rearranged.rows; x++) {
					if (rearranged.at<uchar>(x, y) == 255) {
						if (startX < 0) {
							startX = x;
						}
						else if (x - startX > 20) {

							startX = x;
						}
						if (x - startX <= 20) {
							for (int connectX = startX; connectX <= x; connectX++) {
								rearranged.at<uchar>(connectX, y) = 255;
							}
							startX = x;
						}
					}
				}
			}



			int rearrangedRow = 50;
			int rearrangedCol = 50;
			for (const auto& pair : rowMapping) {
				if (pair.second == rearrangedRow) {
					cout << pair.first << "," << rearrangedCol << endl;
					break;
				}
			}


			//Mat kernel = getStructuringElement(MORPH_RECT, Size(7,7), Point(-1, -1));
			//morphologyEx(result, result, MORPH_DILATE, kernel);
			/*line(result, Point(0, img_temp2.rows), Point(result.cols, img_temp2.rows), Scalar(255), 10);*/

			//imwrite("1.bmp", result);
			resize(rearranged, rearranged, Size(rearranged.cols * 0.3, rearranged.rows * 0.3));
			cv::imshow("Detected Lines", rearranged);

			cv::waitKey(5000);
		}
	}


}
