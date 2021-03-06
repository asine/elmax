#include "Assert.h"
#include "../PortableElmax/Elmax.h"

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestCommentAndCData)
	{
	private:

#ifdef _MICROSOFT
		static TSTR GetFolderPath()
		{
			return _TS("c:\\temp\\");
		}
#else
		static TSTR GetFolderPath()
		{
			return _TS("temp/");
		}
#endif

	public:
		
		TEST_METHOD(SaveReadComment)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadComment.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			Comment comment2 = elem2.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment2.GetContent());
		}
		TEST_METHOD(SaveReadCData)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadCData.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			CData cdata2 = elem2.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata2.GetContent());
		}
		TEST_METHOD(SaveReadCommentCollection)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);
			TSTR strComment2 = _TS("Can I see you?");
			elem.AddComment(strComment2);

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::IsTrue(strComment == vec.at(0).GetContent());

			Assert::IsTrue(strComment2 == vec.at(1).GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadCommentCollection.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCommentCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::IsTrue(strComment == vec2.at(0).GetContent());

			Assert::IsTrue(strComment2 == vec2.at(1).GetContent());
		}
		TEST_METHOD(SaveReadCDataCollection)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);
			TSTR strCData2 = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData2);

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::IsTrue(strCData == vec.at(0).GetContent());

			Assert::IsTrue(strCData2 == vec.at(1).GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadCDataCollection.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCDataCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem.GetCDataCollection();

			Assert::IsTrue(strCData == vec2.at(0).GetContent());

			Assert::IsTrue(strCData2 == vec2.at(1).GetContent());
		}
		TEST_METHOD(DeleteComment)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			Assert::IsTrue(comment.Remove());

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteComment.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::IsTrue(vec2.empty());
		}
		TEST_METHOD(DeleteAllComment)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			Assert::IsTrue(elem.DeleteAllComments());

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteAllComment.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteAllCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::IsTrue(vec2.empty());
		}
		TEST_METHOD(DeleteCData)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			Assert::IsTrue(cdata.Remove());

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteCData.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem2.GetCDataCollection();

			Assert::IsTrue(vec2.empty());
		}
		TEST_METHOD(DeleteAllCData)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			Assert::IsTrue(elem.DeleteAllCData());

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteAllCData.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteAllCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem2.GetCDataCollection();

			Assert::IsTrue(vec2.empty());
		}
		TEST_METHOD(UpdateComment)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			TSTR strUpdate = _TS("Cannot see anything!");
			Assert::IsTrue(comment.Update(strUpdate));

			TSTR file = GetFolderPath() + _TS("UpdateComment.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("UpdateCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			Comment comment2 = elem2.GetCommentCollection().at(0);

			Assert::IsTrue(strUpdate == comment2.GetContent());
		}
		TEST_METHOD(UpdateCData)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			TSTR strUpdate = _TS("<data>Where is my world?</data>");
			Assert::IsTrue(cdata.Update(strUpdate));

			TSTR file = GetFolderPath() + _TS("UpdateCData.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("UpdateCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			CData cdata2 = elem2.GetCDataCollection().at(0);

			Assert::IsTrue(strUpdate == cdata2.GetContent());
		}
		TEST_METHOD(SaveReadEmptyCommentCollection)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::AreEqual((size_t)(0), vec.size());

			TSTR file = GetFolderPath() + _TS("SaveReadEmptyCommentCollection.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadEmptyCommentCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::AreEqual((size_t)(0), vec2.size());
		}
		TEST_METHOD(SaveReadEmptyCDataCollection)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::AreEqual((size_t)(0), vec.size());

			TSTR file = GetFolderPath() + _TS("SaveReadEmptyCDataCollection.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadEmptyCDataCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem.GetCDataCollection();

			Assert::AreEqual((size_t)(0), vec2.size());
		}
		static void executeTests()
		{
			SaveReadComment();
			std::cout<<"SaveReadComment() runs fine!"<<std::endl;
			SaveReadCData();
			std::cout<<"SaveReadCData() runs fine!"<<std::endl;
			SaveReadCommentCollection();
			std::cout<<"SaveReadCommentCollection() runs fine!"<<std::endl;
			SaveReadCDataCollection();
			std::cout<<"SaveReadCDataCollection() runs fine!"<<std::endl;
			DeleteComment();
			std::cout<<"DeleteComment() runs fine!"<<std::endl;
			DeleteAllComment();
			std::cout<<"DeleteAllComment() runs fine!"<<std::endl;
			DeleteCData();
			std::cout<<"DeleteCData() runs fine!"<<std::endl;
			DeleteAllCData();
			std::cout<<"DeleteAllCData() runs fine!"<<std::endl;
			UpdateComment();
			std::cout<<"UpdateComment() runs fine!"<<std::endl;
			UpdateCData();
			std::cout<<"UpdateCData() runs fine!"<<std::endl;
			SaveReadEmptyCommentCollection();
			std::cout<<"SaveReadEmptyCommentCollection() runs fine!"<<std::endl;
			SaveReadEmptyCDataCollection();
			std::cout<<"SaveReadEmptyCDataCollection() runs fine!"<<std::endl;
		}

	};
}