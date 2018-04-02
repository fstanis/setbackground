package setbackground_test

import (
	"log"
	"github.com/fstanis/setbackground/go"
)

func ExampleSetBackground() {
	image := "path/to/image.jpg"
	err := setbackground.SetBackground(image, setbackground.StyleCenter)
	if err != nil {
		log.Fatal(err)
	}
}
