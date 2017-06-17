#pragma once
#include "Corrector_lite.h"
#include <vcclr.h>

namespace Window_Corrector_lite {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Window_Corrector_lite
	/// </summary>
	public ref class Window_Corrector_lite : public System::Windows::Forms::Form
	{
	public:
		Corrector_lite *base = new Corrector_lite();
		Window_Corrector_lite(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			const char file[] = { "1.txt" };

			base->open(file);
			base->Create_dictionary();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window_Corrector_lite()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  Corrected_word;
	private: System::Windows::Forms::ListBox^  Show_answer;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Corrected_word = (gcnew System::Windows::Forms::TextBox());
			this->Show_answer = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// Corrected_word
			// 
			this->Corrected_word->Location = System::Drawing::Point(12, 29);
			this->Corrected_word->Name = L"Corrected_word";
			this->Corrected_word->Size = System::Drawing::Size(187, 20);
			this->Corrected_word->TabIndex = 1;
			this->Corrected_word->TextChanged += gcnew System::EventHandler(this, &Window_Corrector_lite::Corrected_word_TextChanged);
			// 
			// Show_answer
			// 
			this->Show_answer->FormattingEnabled = true;
			this->Show_answer->Location = System::Drawing::Point(12, 86);
			this->Show_answer->Name = L"Show_answer";
			this->Show_answer->Size = System::Drawing::Size(187, 186);
			this->Show_answer->TabIndex = 3;
			this->Show_answer->SelectedIndexChanged += gcnew System::EventHandler(this, &Window_Corrector_lite::Show_answer_SelectedIndexChanged);
			// 
			// Window_Corrector_lite
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(266, 330);
			this->Controls->Add(this->Show_answer);
			this->Controls->Add(this->Corrected_word);
			this->Name = L"Window_Corrector_lite";
			this->Text = L"Window_Corrector_lite";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Show_answer_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void Corrected_word_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		String ^text = this->Corrected_word->Text;
		vector<wchar_t> text1;
		pin_ptr<const wchar_t> wch = PtrToStringChars(text);
		const wchar_t *qwer = wch;
		vector<suggest> answer;
		answer = base->Find(qwer, text->Length);
		text1.clear();
		String^ word;
		Show_answer->Items->Clear();
		for (int i = 0; i < answer.size(); i++)
		{
			for (int j = 0; j < answer[i].length; j++)
				word += answer[i].word[j];
			Show_answer->Items->Add(word);
			word = "";
		}
	}

	};
}
