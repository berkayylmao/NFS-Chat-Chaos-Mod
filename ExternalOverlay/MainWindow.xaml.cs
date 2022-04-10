using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Windows;

namespace ExternalOverlay {
  public partial class MainWindow : Window {
    public const String CONST_FilePath = "ExternalOverlayUpdates.entry";

    private readonly Thread updateThread;
    private Boolean exitApplication = false;

    private void OnWindowClosing(Object sender, System.ComponentModel.CancelEventArgs e) {
      this.exitApplication = true;
      updateThread.Abort();
    }

    public void UpdateFn() {
      while (!this.exitApplication) {
        try {
          if (Process.GetProcessesByName("speed").Length == 0) {
            this.exitApplication = true;
            break;
          }

          String[] lines = File.ReadAllLines(CONST_FilePath);
          if (lines[0] == "BYE") {
            this.exitApplication = true;
            break;
          }

          Boolean visibility_flag = Convert.ToBoolean(lines[1]);
          this.panel.Dispatcher.Invoke(() =>
          {
            this.panel.Visibility = visibility_flag ? Visibility.Visible : Visibility.Hidden;
            foreach (Object child in panel.Children) {
              if (!(child is FrameworkElement fe))
                continue;

              fe.Dispatcher.Invoke(() => fe.Visibility = this.panel.Visibility);
            }
          });
          if (!visibility_flag)
            continue;
          if (lines.Length != 9)
            continue;

          var x = Convert.ToDouble(lines[5]);
          var y = Convert.ToDouble(lines[6]);
          var font_size =  Convert.ToDouble(lines[7]) * 0.75d;
          var spacing = Convert.ToDouble(lines[8]) * 0.8d;

          this.effect1.Dispatcher.Invoke(() =>
          {
            this.effect1.Text = $"!cv 1: {lines[2]}";
            this.effect1.FontSize = font_size;
            this.effect1.Margin = new Thickness(x, y, 0.0d, spacing);
          });
          this.effect2.Dispatcher.Invoke(() =>
          {
            this.effect2.Text = $"!cv 2: {lines[3]}";
            this.effect2.FontSize = font_size;
            this.effect2.Margin = new Thickness(x, 0.0d, 0.0d, spacing);
          });
          this.effect3.Dispatcher.Invoke(() =>
          {
            this.effect3.Text = $"!cv 3: {lines[4]}";
            this.effect3.FontSize = font_size;
            this.effect3.Margin = new Thickness(x, 0.0d, 0.0d, spacing);
          });

        } catch (Exception) {
        }
        Thread.Sleep(100);
      }
      Environment.Exit(0);
    }

    public MainWindow() {
      this.InitializeComponent();
      this.Left = this.Top = 50;

      this.updateThread = new Thread(this.UpdateFn);
      this.updateThread.SetApartmentState(ApartmentState.MTA);
      this.updateThread.Start();
    }
  }
}
