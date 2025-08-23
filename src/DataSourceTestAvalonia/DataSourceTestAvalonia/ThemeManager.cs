using Avalonia;
using Avalonia.Styling;
using System;

namespace DataSourceTestAvalonia
{
    public enum AppTheme
    {
        Light,
        Dark
    }

    public class ThemeManager
    {
        private static ThemeManager? _instance;
        private AppTheme _currentTheme = AppTheme.Light;

        public static ThemeManager Instance => _instance ??= new ThemeManager();

        public AppTheme CurrentTheme => _currentTheme;

        public event EventHandler<AppTheme>? ThemeChanged;

        private ThemeManager()
        {
            // Set initial theme
            ApplyTheme(_currentTheme);
        }

        public void SetTheme(AppTheme theme)
        {
            if (_currentTheme != theme)
            {
                _currentTheme = theme;
                ApplyTheme(theme);
                ThemeChanged?.Invoke(this, theme);
            }
        }

        public void ToggleTheme()
        {
            SetTheme(_currentTheme == AppTheme.Light ? AppTheme.Dark : AppTheme.Light);
        }

        private void ApplyTheme(AppTheme theme)
        {
            var app = Application.Current;
            if (app != null)
            {
                var themeVariant = theme switch
                {
                    AppTheme.Dark => ThemeVariant.Dark,
                    AppTheme.Light => ThemeVariant.Light,
                    _ => ThemeVariant.Light
                };

                app.RequestedThemeVariant = themeVariant;
            }
        }

        public string GetThemeDisplayName()
        {
            return _currentTheme switch
            {
                AppTheme.Dark => "🌙 Dark",
                AppTheme.Light => "☀️ Light",
                _ => "☀️ Light"
            };
        }

        public string GetNextThemeDisplayName()
        {
            return _currentTheme switch
            {
                AppTheme.Dark => "☀️ Light",
                AppTheme.Light => "🌙 Dark",
                _ => "🌙 Dark"
            };
        }
    }
}
