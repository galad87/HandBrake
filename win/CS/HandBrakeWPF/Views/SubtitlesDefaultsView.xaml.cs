// --------------------------------------------------------------------------------------------------------------------
// <copyright file="SubtitlesDefaultsView.xaml.cs" company="HandBrake Project (http://handbrake.fr)">
//   This file is part of the HandBrake source code - It may be used under the terms of the GNU General Public License.
// </copyright>
// <summary>
//   Interaction logic for SubtitlesDefaultsView.xaml
// </summary>
// --------------------------------------------------------------------------------------------------------------------

namespace HandBrakeWPF.Views
{
    using System.Windows;

    using HandBrakeWPF.ViewModels;

    public partial class SubtitlesDefaultsView : Window
    {
        public SubtitlesDefaultsView()
        {
            this.InitializeComponent();
        }

        private void Apply_OnClick(object sender, RoutedEventArgs e)
        {
            ((SubtitlesDefaultsViewModel)DataContext).IsApplied = true;
            this.Close();
        }
    }
}
