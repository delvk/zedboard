#include "../inc/face_regconition.hpp"
#include "../inc/func_face_regcontion.hpp"
int main(int argc, const char *argv[])
{
	//initial variables
	string path_training_set ="/mnt/training/csv/train_set.csv";
	string output_folder = "/mnt/output";

	//Checking arguments
	cout << "usage: " << argv[0] << endl;
	cout << "<path_training_set> <output_folder>" << endl;
	cout << "\n----------------------------------------------------------\n"
		 << endl;

//	if (argc < 2)
//	{
//		cout << "Please point to training_set" << endl;
//		cout<<"Exiting"<<endl;
//		exit(-1);
//	}
//	else if (argc < 3)
//	{
//		path_training_set = string(argv[1]);
//		cout << "You only input database_path, is this okay (Y/N) ?" << endl;
//	}
//	else
//	{
//		path_training_set = string(argv[1]);
//		output_folder = string(argv[2]);
//		cout << "Is this okay (Y/N) ?" << endl;
//	}
	cout << "- path_training_set: " << path_training_set << endl;
	cout << "- output_folder: " << output_folder << endl;
//	if (!checkUserEnter())
//	{
//		cout << "See ya later, bye !" << endl;
//		return 0;
//	}
	// These vectors hold the images and corresponding labels.
	vector<Mat> images;
	vector<int> labels;
	// Read in the data. This can fail if no valid
	// input filename is given.
	try
	{
		read_csv(path_training_set, images, labels);
	}
	catch (const cv::Exception &e)
	{
		cerr << "Error opening file \"" << path_training_set << "\". Reason: " << e.msg << endl;
		// nothing more we can do
		exit(-1);
	}
	// Quit if there are not enough images for this demo.
	if (images.size() <= 1)
	{
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		exit(-1);
	}
	//size 180x200;
	cout<<"Image 0: "<<images[0].size()<<endl;
	bool ok = true;
	for (unsigned int i = 0; i < images.size(); i++)
	{
		if (images[i].size() != Size(180,200))
		{
			cout << "Test Errror: " << "image["<<i<<": "<<images[i].size()<<endl;
			ok = false;
		}

	}
	if (!ok)
	{
		cout << "Kich thuoc yeu cau 180x200, xin thu lai voi tap du lieu khac" << endl;
		return -1;
	}
	else{
		cout<<"Test size: pass"<<endl;
	}
//
	/* create output folder */
	const int dir_err = mkdir(output_folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err)
	{
		printf("Couldn't creating directory output, maybe already exit!\n");
	}
	else cout<<"create "<<output_folder<<endl;

//	/*---TRAINING---*/
	cout<<"Start training ..."<<endl;
	Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();
	model->train(images, labels);


	string filename = output_folder+"/model.yml";
	FileStorage fs;
	fs.open(filename, FileStorage::WRITE | FileStorage::MEMORY);
	model->write(filename);
	fs.release();

	bool temp = !model.empty();
	if (temp) model->clear();
	cout<<"Finished"<<endl;

	//Double check
	cout<<"Checking output file "<<endl;
	model->read(filename);
	if (model->empty())
	{
		cout << "Model save khong thanh cong " << endl;
	}
	else cout << "Save model successful" << endl;
	return 0;
}
