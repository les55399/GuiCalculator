#include <Windows.h>
#include <string>
#include <cmath>
using namespace System;
using namespace System::Windows::Forms;

public ref class Calculator : public Form {
private:
    TextBox^ display;
    String^ currentInput = "";
    double operand1 = 0;
    String^ operation = "";

public:
    Calculator() {
        this->Text = "C++ GUI Calculator";
        this->Width = 300;
        this->Height = 400;

        display = gcnew TextBox();
        display->Dock = DockStyle::Top;
        display->Font = gcnew Drawing::Font("Segoe UI", 20);
        display->ReadOnly = true;
        display->TextAlign = HorizontalAlignment::Right;
        display->Height = 50;
        this->Controls->Add(display);

        TableLayoutPanel^ panel = gcnew TableLayoutPanel();
        panel->Dock = DockStyle::Fill;
        panel->ColumnCount = 4;
        panel->RowCount = 4;
        this->Controls->Add(panel);

        array<String^>^ buttons = { "7","8","9","/",
                                    "4","5","6","*",
                                    "1","2","3","-",
                                    "C","0","=","+" };

        for each (String ^ b in buttons) {
            Button^ btn = gcnew Button();
            btn->Text = b;
            btn->Font = gcnew Drawing::Font("Segoe UI", 14);
            btn->Dock = DockStyle::Fill;
            btn->Click += gcnew EventHandler(this, &Calculator::onClick);
            panel->Controls->Add(btn);
        }
    }

    void onClick(Object^ sender, EventArgs^ e) {
        Button^ b = dynamic_cast<Button^>(sender);
        String^ txt = b->Text;

        if (txt == "C") {
            display->Text = "";
            currentInput = "";
            operand1 = 0;
            operation = "";
        }
        else if (txt == "+" || txt == "-" || txt == "*" || txt == "/") {
            operand1 = Convert::ToDouble(currentInput);
            operation = txt;
            currentInput = "";
        }
        else if (txt == "=") {
            double operand2 = Convert::ToDouble(currentInput);
            double result = 0;
            if (operation == "+") result = operand1 + operand2;
            else if (operation == "-") result = operand1 - operand2;
            else if (operation == "*") result = operand1 * operand2;
            else if (operation == "/") {
                if (operand2 == 0) {
                    display->Text = "Error";
                    return;
                }
                result = operand1 / operand2;
            }
            display->Text = result.ToString();
            currentInput = result.ToString();
        }
        else {
            currentInput += txt;
            display->Text = currentInput;
        }
    }
};

[STAThreadAttribute]
int main() {
    Application::EnableVisualStyles();
    Application::Run(gcnew Calculator());
    return 0;
}
