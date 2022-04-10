using System.Windows;
using System.Windows.Controls;

namespace ExternalOverlay {
  public class ChildrenMarginSetter {
    public static Thickness GetMargin(DependencyObject obj) {
      return (Thickness)obj.GetValue(MarginProperty);
    }

    public static void SetMargin(DependencyObject obj, Thickness value) {
      obj.SetValue(MarginProperty, value);
    }

    public static readonly DependencyProperty MarginProperty =
        DependencyProperty.RegisterAttached("Margin", typeof(Thickness), typeof(ChildrenMarginSetter), new UIPropertyMetadata(new Thickness(), CreateThicknesForChildren));

    public static void CreateThicknesForChildren(object sender, DependencyPropertyChangedEventArgs e) {
      var panel = sender as Panel;

      if (panel == null)
        return;

      foreach (var child in panel.Children) {
        var fe = child as FrameworkElement;

        if (fe == null)
          continue;

        fe.Margin = GetMargin(panel);
      }
    }


  }
}
